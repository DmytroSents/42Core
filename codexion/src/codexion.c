/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 02:12:17 by dbrusent          #+#    #+#             */
/*   Updated: 2026/08/09 20:33:23 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	main(int argc, char *argv[])
{
	t_data	p_tr;
	t_queue	my_q;
	int		ft_errno;

	ft_errno = argc;
	ft_errno = parse_args(argv, &p_tr, &ft_errno, 0);
	if (ft_errno)
		return (print_stuff(0, ft_errno));
	if (fill_struct(&p_tr) < 0)
		return (-1);
	if (queue_init(&p_tr, &my_q) < 0)
		return (ft_free(&p_tr, NULL, -2));
	p_tr.ready_q = &my_q;
	p_tr.time_0 = time_ms(NULL, "start");
	if (create_threads(&p_tr, 0))
		return (ft_free(&p_tr, &my_q, -3));
	ft_destroy_join(&p_tr, p_tr.coders_num, 'J', 0);
	return (ft_free(&p_tr, &my_q, 0));
}

int	parse_args(char *argv[], t_data	*p, int *ft_err, int i)
{
	int	arg_i[7];

	if (*ft_err != 9)
		return (9);
	if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
		return (8);
	memset(arg_i, 0, 7 * sizeof(int));
	while (++i < 8)
	{
		*ft_err = 0;
		arg_i[i - 1] = atoi(argv[i]);
		if (ft_strisnum(argv[i]) || (i < 7 && arg_i[i - 1] <= 0))
			return (i);
	}
	if (arg_i[6] < 0)
		return (i);
	p->coders_num = (size_t)(arg_i[0]);
	p->burnout_time = (size_t)arg_i[1];
	p->compile_time = (size_t)arg_i[2];
	p->debugin_time = (size_t)arg_i[3];
	p->refactor_time = (size_t)arg_i[4];
	p->compile_req_num = (size_t)arg_i[5];
	p->dongle_cooldown = (size_t)arg_i[6];
	p->scheduler = argv[8];
	return (*ft_err);
}

static void	fill_coder(t_data *p, size_t i)
{
	p->coders[i].id = i;
	p->coders[i].data = p;
	p->dongle[i].state = READY;
	p->coders[i].state = WAITING;
	p->coders[i].right = &(p->dongle[i]);
	if (i == 0)
		p->coders[i].left = &(p->dongle[p->coders_num - 1]);
	else
		p->coders[i].left = &(p->dongle[i - 1]);
	p->coders[i].comp_todo = p->compile_req_num;
	p->coders[i].previos_compile = 0;
}

int	fill_struct(t_data *p)
{
	size_t	i;

	i = 0;
	p->stop = 0;
	p->coders = malloc(sizeof(t_coder) * (p->coders_num));
	if (p->coders == NULL)
		return (-1);
	p->dongle = malloc(sizeof(t_dongle) * (p->coders_num));
	if (p->dongle == NULL)
		return (ft_free(p, NULL, -2));
	while (i < p->coders_num)
	{
		fill_coder(p, i);
		i++;
	}
	return (0);
}

int	print_stuff(t_data *p, int error)
{
	(void)p;
	if (error)
		write(2, "Error\n", 6);
	return (error);
}
