/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 02:41:18 by dbrusent          #+#    #+#             */
/*   Updated: 2026/07/12 22:44:53 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

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
		if (i < 7 && arg_i[i - 1] <= 0)
			return (i);
	}
	if (arg_i[6] < 0)
		return (i);
	p->coders_num = (size_t)(arg_i[0] + 1);
	p->burnout_time = (size_t)arg_i[1];
	p->compile_time = (size_t)arg_i[2];
	p->debugin_time = (size_t)arg_i[3];
	p->refactor_time = (size_t)arg_i[4];
	p->compile_req_num = (size_t)arg_i[5];
	p->dongle_cooldown = (size_t)arg_i[6];
	return (*ft_err);
}

int	fill_struct(t_data *p)
{
	int	i;

	i = 0;
	p->coders = malloc(sizeof(t_coder) * (p->coders_num));
	if (p->coders == NULL)
		return (-1);
	p->dongle = malloc(sizeof(t_dongle) * (p->coders_num));
	if (p->dongle == NULL)
		return (ft_free(p, -2));
	while (++i < p->coders_num)
	{
		p->coders[i].id = i;
		p->coders[i].data = p;
		p->dongle[i].state = READY;
		p->coders[i].state = WAITING;
		p->coders[i].right = &(p->dongle[i]);
		p->coders[i].left = &(p->dongle[i - 1]);
		p->coders[i].comp_todo = p->compile_req_num;
	}
	p->dongle[0].state = READY;
	p->print_mutex = &(p->dongle[0].ptr);
	p->coders[1].left = &(p->dongle[p->coders_num - 1]);
	return (0);
}

//free(p);
int	ft_free(t_data *p, int ex_code)
{
	if (p == NULL)
		return (-1);
	if (p->coders)
		free(p->coders);
	if (p->dongle)
		free(p->dongle);
	return (ex_code);
}

void	ft_destroy_join(t_data *p, int amount, char chr)
{
	int	j;

	j = 0;
	if (chr == 'M')
	{
		while (j < amount)
			pthread_mutex_destroy(&p->dongle[j++].ptr);
	}
	else if (chr == 'J')
	{
		while (j < amount)
		{
			p->coders[j].state = 0;
			pthread_join(p->coders[j++].thread, NULL);
		}
		j = 0;
		amount = p->coders_num;
		while (j < amount)
			pthread_mutex_destroy(&p->dongle[j++].ptr);
	}
	return ;
}

int	create_threads(t_data *p, int i)
{
	while (i < p->coders_num)
	{
		if (pthread_mutex_init(&p->dongle[i].ptr, NULL) != 0)
		{
			ft_destroy_join(p, i, 'M');
			return (-1);
		}
		i++;
	}
	pthread_create(&p->coders[0].thread, NULL, &monitor, &p);
	i = 1;
	while (i < p->coders_num)
	{
		if (pthread_create(&p->coders[i].thread, NULL, &routine, &p->coders[i]))
		{
			ft_destroy_join(p, i, 'J');
			return (-1);
		}
		i++;
	}
	return (0);
}
