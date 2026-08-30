/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 19:32:42 by dbrusent          #+#    #+#             */
/*   Updated: 2026/08/09 19:43:46 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	ft_free(t_data *p, t_queue *q, int ex_code)
{
	if (p == NULL)
		return (-1);
	if (q)
		free(q->arr);
	if (p->coders)
		free(p->coders);
	if (p->dongle)
		free(p->dongle);
	return (ex_code);
}

int	is_stopped(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->monitor_mut);
	stop = data->stop;
	pthread_mutex_unlock(&data->monitor_mut);
	return (stop);
}

void	sleep_partial(t_coder *p, size_t ms)
{
	size_t	start;

	start = (size_t)time_ms(p, 0);
	while ((size_t)time_ms(p, 0) - start < ms && !is_stopped(p->data))
		usleep((ms * 1000) / 10);
}

void	do_action(t_coder *p, int act)
{
	pthread_mutex_lock(&p->mut_self);
	p->state = act;
	pthread_mutex_unlock(&p->mut_self);
	if (act == WAITING)
		return ;
	print_report(p, p->data, 0);
	if (act == DEBUGING)
		sleep_partial(p, p->data->debugin_time);
	else if (act == REFACTOR)
		sleep_partial(p, p->data->refactor_time);
}
