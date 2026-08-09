/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 02:41:18 by dbrusent          #+#    #+#             */
/*   Updated: 2026/08/09 20:53:07 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	queue_init(t_data *p, t_queue *q)
{
	if (!q || !p)
		return (0);
	q->arr = NULL;
	q->arr = (t_coder **)malloc((p->coders_num) * sizeof(t_coder *));
	if (!q->arr)
		return (-1);
	memset(q->arr, 0, (p->coders_num) * sizeof(t_coder *));
	q->rear = 0;
	q->count = 0;
	q->front = 0;
	q->capacity = p->coders_num;
	if (strcmp(p->scheduler, "fifo") == 0)
	{
		q->pop = fifo_pop;
		q->push = fifo_push;
	}
	if (strcmp(p->scheduler, "edf") == 0)
	{
		q->pop = edf_extract;
		q->push = edf_insert;
	}
	return (0);
}

ssize_t	time_ms(t_coder *ptr, char *str)
{
	struct timeval	tv;
	size_t			absolute;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	if (str && strcmp(str, "dongle") == 0)
		return ((ssize_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
	if (str && strcmp(str, "start") == 0)
		return ((ssize_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
	absolute = (size_t)tv.tv_sec * 1000 + (size_t)tv.tv_usec / 1000;
	return ((ssize_t)(absolute - ptr->data->time_0));
}

int	ft_destroy_join(t_data *p, int amount, char chr, int j)
{
	if (chr == 'M')
	{
		while (j < amount)
		{
			pthread_cond_destroy(&p->coders[j].permi_cond);
			pthread_mutex_destroy(&p->coders[j++].mut_self);
		}
	}
	else if (chr == 'J')
	{
		while (j < amount)
			pthread_join(p->coders[j++].thread, NULL);
		j = 0;
		amount = p->coders_num;
		{
			pthread_cond_destroy(&p->coders[j].permi_cond);
			pthread_mutex_destroy(&p->coders[j++].mut_self);
		}
	}
	pthread_join(p->monitor, NULL);
	pthread_mutex_destroy(&p->monitor_mut);
	pthread_cond_destroy(&p->monitor_cond);
	pthread_mutex_destroy(&p->print_mutex);
	return (-1);
}

int	create_threads(t_data *p, int i)
{
	pthread_mutex_init(&p->monitor_mut, NULL);
	pthread_cond_init(&p->monitor_cond, NULL);
	if (pthread_mutex_init(&p->print_mutex, NULL) != 0)
		return (-1);
	while (i < p->coders_num)
	{
		if (pthread_mutex_init(&p->coders[i].mut_self, NULL) != 0)
			return (ft_destroy_join(p, i, 'M', 0));
		if (pthread_cond_init(&p->coders[i].permi_cond, NULL) != 0)
			return (ft_destroy_join(p, i, 'M', 0));
		i++;
	}
	if (pthread_create(&p->monitor, NULL, &monitor, p) != 0)
		return (ft_destroy_join(p, i, 'M', 0));
	i = 0;
	while (i < p->coders_num)
	{
		if (pthread_create(&p->coders[i].thread, NULL, &routine, &p->coders[i]))
			return (ft_destroy_join(p, i, 'J', 0));
		i++;
	}
	return (0);
}

int	ft_strisnum(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}
