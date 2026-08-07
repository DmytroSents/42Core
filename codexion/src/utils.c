/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 02:41:18 by dbrusent          #+#    #+#             */
/*   Updated: 2026/08/06 18:52:28 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

ssize_t	time_ms(t_coder *ptr, char *str)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	if (str && strcmp(str, "dongle") == 0)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	if (str && strcmp(str, "start") == 0)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	ptr->elapsed = (size_t)tv.tv_sec * 1000;
	ptr->elapsed += (size_t)tv.tv_usec / 1000;
	if (str && strcmp(str, "last_") == 0)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return ((size_t)ptr->elapsed - ptr->last_compile);
}

//free(p);
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

int	ft_destroy_join(t_data *p, int amount, char chr)
{
	int	j;

	j = 0;
	if (chr == 'M')
	{
		pthread_mutex_destroy(&p->print_mutex);
		while (j < amount)
			pthread_mutex_destroy(&p->dongle[j++].ptr);
	}
	else if (chr == 'J')
	{
		while (j < amount)
		{
			p->stop = 1;
			pthread_join(p->coders[j++].thread, NULL);
		}
		j = 0;
		pthread_mutex_destroy(&p->print_mutex);
		amount = p->coders_num;
		while (j < amount)
			pthread_mutex_destroy(&p->dongle[j++].ptr);
	}
	return (-1);
}

int	create_threads(t_data *p, int i)
{
	if (pthread_mutex_init(&p->print_mutex, NULL) != 0)
		return (-1);
	while (i < p->coders_num)
	{
		if (pthread_mutex_init(&p->dongle[i].ptr, NULL) != 0)
			return (ft_destroy_join(p, i, 'M'));
		i++;
	}
	if (pthread_create(&p->monitor, NULL, &monitor, p) != 0)
		return (ft_destroy_join(p, i, 'M'));
	i = 0;
	pthread_mutex_lock(&p->print_mutex);
	while (i < p->coders_num)
	{
		if (pthread_create(&p->coders[i].thread, NULL, &routine, &p->coders[i]))
			return (ft_destroy_join(p, i, 'J'));
		i++;
		usleep(500);
	}
	p->time_0 = time_ms(&p->coders[0], "start");
	pthread_mutex_unlock(&p->print_mutex);
	return (0);
}

int	ft_strisnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}
