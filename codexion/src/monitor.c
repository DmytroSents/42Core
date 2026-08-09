/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 19:33:38 by dbrusent          #+#    #+#             */
/*   Updated: 2026/08/09 19:54:45 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	*monitor(void *data)
{
	t_data	*p;
	size_t	now;

	p = (t_data *)data;
	while (1)
	{
		pthread_mutex_lock(&p->monitor_mut);
		if (p->stop)
		{
			pthread_mutex_unlock(&p->monitor_mut);
			break ;
		}
		now = time_ms(NULL, "start") - p->time_0;
		if (check_burnout(p, now, 0, 1))
		{
			pthread_mutex_unlock(&p->monitor_mut);
			break ;
		}
		scheduler(p, now, 0);
		pthread_mutex_unlock(&p->monitor_mut);
		usleep(1111);
	}
	return (NULL);
}

int	check_burnout(t_data *data, size_t now, size_t i, int done)
{
	while (i < data->coders_num)
	{
		if (data->coders[i].comp_todo > 0)
			done = 0;
		if (now - data->coders[i].previos_compile > data->burnout_time)
		{
			pthread_mutex_lock(&data->coders[i].mut_self);
			data->coders[i].state = BURNOUT;
			pthread_mutex_unlock(&data->coders[i].mut_self);
			print_report(&data->coders[i], data, 0);
			data->stop = 1;
			broadcast_all(data);
			return (1);
		}
		i++;
	}
	if (done)
	{
		data->stop = 1;
		broadcast_all(data);
		return (1);
	}
	return (0);
}

void	scheduler(t_data *data, size_t now, size_t i)
{
	t_coder	*mayb_next;

	while (i < data->coders_num)
	{
		if (data->dongle[i].state == COOLDOWN
			&& now - data->dongle[i].release_time >= data->dongle_cooldown)
			data->dongle[i].state = READY;
		i++;
	}
	while (1)
	{
		mayb_next = queue_peek(data->ready_q, data->scheduler);
		if (!mayb_next)
			break ;
		if (mayb_next->left->state != READY || mayb_next->right->state != READY)
			break ;
		if (strcmp(data->scheduler, "fifo") == 0)
			data->ready_q->pop(data->ready_q);
		else
			data->ready_q->pop(data->ready_q);
		mayb_next->left->state = IN_USE;
		mayb_next->right->state = IN_USE;
		mayb_next->permision = 1;
		pthread_cond_signal(&mayb_next->permi_cond);
	}
}

void	broadcast_all(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->coders_num)
	{
		pthread_cond_broadcast(&data->coders[i].permi_cond);
		i++;
	}
}
