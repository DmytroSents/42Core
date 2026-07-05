/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 02:41:18 by dbrusent          #+#    #+#             */
/*   Updated: 2026/07/05 05:57:02 by dbrusent         ###   ########.fr       */
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
	p->dongles = malloc(sizeof(pthread_mutex_t) * (p->coders_num));
	if (p->dongles == NULL)
		return (ft_free(p, -2));
	while (i < p->coders_num)
	{
		p->coders[i].data = p;
		p->coders[i].id = i;
		p->coders[i].left = &(p->dongles[i - 1]);
		p->coders[i].right = &(p->dongles[i]);
		i++;
	}
	p->coders[1].left = &(p->dongles[p->coders_num - 1]);
	return (0);
}

//free(p);
int	ft_free(t_data *p, int ex_code)
{
	if (p == NULL)
		return (-1);
	if (p->coders)
		free(p->coders);
	if (p->dongles)
		free(p->dongles);
	return (ex_code);
}

void	print_stuff(t_data *p)
{
	int	i;

	i = 0;
	while (++i < p->coders_num)
	{
		printf("ID:%zu; Dongle_L:%p;", p->coders[i].id, p->coders[i].left);
		printf("Dongle_R:%p\n", p->coders[i].right);
	}
	// printf("Coders_num: %zu;\n", p->coders_num);
	// printf("Burnout_time: %zu;\n", p->burnout_time);
	// printf("Compile_time: %zu;\n", p->compile_time);
	// printf("Debugin_time: %zu;\n", p->debugin_time);
	// printf("Refactor_time: %zu;\n", p->refactor_time);
	// printf("Compile_req_num: %zu;\n", p->compile_req_num);
	// printf("Dongle_cooldown: %zu\n", p->dongle_cooldown);
}
