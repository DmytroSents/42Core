/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 10:56:11 by dbrusent          #+#    #+#             */
/*   Updated: 2026/08/09 20:59:23 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

	/* request dongle ? compile : die
	release dongles
	debug -> refactor
	wrap it inside while (lo0p)
	change state_variables every step
	implement time-functions	*/
	/*  Ask scheduler for both dongles.
	Wait until granted.
	Mark both dongles as taken in shared state.
	Print two take lines.
	Set last_compile_start.
	Print compiling.
	Sleep for compile time.
	Release both dongles and start cooldown.
	Move to debugging/refactoring	*/

void	*routine(void *coder)
{
	t_coder	*p;

	p = (t_coder *)coder;
	while (!p->data->stop && p->comp_todo)
	{
		if (request_dongles(p, p->data) < 0)
			break ;
		compile(p, p->data);
		if (p->comp_todo == 0)
		{
			pthread_mutex_lock(&p->data->print_mutex);
			printf("%zums " GREEN "%zu " RESET "has", time_ms(p, 0), p->id + 1);
			printf(GREEN " finished " RESET "simulation\n");
			pthread_mutex_unlock(&p->data->print_mutex);
			break ;
		}
		pthread_mutex_lock(&p->mut_self);
		p->state = DEBUGING;
		pthread_mutex_unlock(&p->mut_self);
		print_report(p, p->data, 0);
		usleep((p->data->debugin_time) * 1000);
		if (p->data->stop)
			break ;
		pthread_mutex_lock(&p->mut_self);
		p->state = REFACTOR;
		pthread_mutex_unlock(&p->mut_self);
		print_report(p, p->data, 0);
		usleep((p->data->refactor_time) * 1000);
		if (p->data->stop)
			break ;
		pthread_mutex_lock(&p->mut_self);
		p->state = WAITING;
		pthread_mutex_unlock(&p->mut_self);
	}
	return (NULL);
}

int	compile(t_coder *p, t_data *t)
{
	print_report(p, t, 'L');
	print_report(p, t, 'R');
	pthread_mutex_lock(&t->monitor_mut);
	p->previos_compile = (size_t)time_ms(p, "last_");
	pthread_mutex_unlock(&t->monitor_mut);
	pthread_mutex_lock(&p->mut_self);
	p->state = COMPILNG;
	pthread_mutex_unlock(&p->mut_self);
	print_report(p, t, 0);
	usleep((p->data->compile_time) * 1000);
	pthread_mutex_lock(&t->monitor_mut);
	p->comp_todo = p->comp_todo - 1;
	pthread_mutex_unlock(&t->monitor_mut);
	release_dongles(p, t);
	return (0);
}

int	print_report(t_coder *p, t_data *t, char dg)
{
	int		i;
	int		print_state;

	i = -1;
	pthread_mutex_lock(&p->mut_self);
	print_state = p->state;
	pthread_mutex_unlock(&p->mut_self);
	pthread_mutex_lock(&t->print_mutex);
	if (print_state == BURNOUT)
		i = printf("%zu_ms %zu burned out\n", time_ms(p, 0), p->id + 1);
	else if (print_state == COMPILNG)
		i = printf("%zu_ms %zu is compiling\n", time_ms(p, 0), p->id + 1);
	else if (print_state == DEBUGING)
		i = printf("%zu_ms %zu is debugging\n", time_ms(p, 0), p->id + 1);
	else if (print_state == REFACTOR)
		i = printf("%zu_ms %zu is refactoring\n", time_ms(p, 0), p->id + 1);
	else if (print_state == WAITING && dg)
		i = printf("%zu_ms %zu took %c dongle\n", time_ms(p, 0), p->id + 1, dg);
	pthread_mutex_unlock(&t->print_mutex);
	return (i);
}

int	request_dongles(t_coder *coder, t_data *p)
{
	pthread_mutex_lock(&p->monitor_mut);
	coder->permision = 0;
	coder->deadline = coder->previos_compile + p->burnout_time;
	p->ready_q->push(p->ready_q, coder);
	while (!coder->permision && !p->stop)
		pthread_cond_wait(&coder->permi_cond, &p->monitor_mut);
	if (p->stop)
	{
		pthread_mutex_unlock(&p->monitor_mut);
		return (-1);
	}
	pthread_mutex_unlock(&p->monitor_mut);
	return (0);
}

void	release_dongles(t_coder *coder, t_data *p)
{
	pthread_mutex_lock(&p->monitor_mut);
	coder->left->state = COOLDOWN;
	coder->left->release_time = (size_t)time_ms(NULL, "start") - p->time_0;
	coder->right->state = COOLDOWN;
	coder->right->release_time = (size_t)time_ms(NULL, "start") - p->time_0;
	pthread_mutex_unlock(&p->monitor_mut);
}
