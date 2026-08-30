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
	while (!is_stopped(p->data) && p->comp_todo)
	{
		if (request_dongles(p, p->data) < 0)
			break ;
		compile(p, p->data);
		if (is_stopped(p->data))
			break ;
		if (p->comp_todo == 0)
		{
			print_report(p, p->data, 'F');
			break ;
		}
		do_action(p, DEBUGING);
		if (is_stopped(p->data))
			break ;
		do_action(p, REFACTOR);
		if (is_stopped(p->data))
			break ;
		do_action(p, WAITING);
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
	sleep_partial(p, p->data->compile_time);
	pthread_mutex_lock(&t->monitor_mut);
	p->comp_todo = p->comp_todo - 1;
	p->left->state = COOLDOWN;
	p->left->release_time = (size_t)time_ms(NULL, "start") - t->time_0;
	p->right->state = COOLDOWN;
	p->right->release_time = (size_t)time_ms(NULL, "start") - t->time_0;
	pthread_mutex_unlock(&t->monitor_mut);
	return (0);
}

static void	print_msg(t_coder *p, char dg, int state)
{
	if (dg == 'F')
		printf("%zums " GREEN "%zu " RESET "has finished simulation\n",
			time_ms(p, 0), p->id + 1);
	else if (state == BURNOUT)
		printf("%zu_ms %zu burned out\n", time_ms(p, 0), p->id + 1);
	else if (state == COMPILNG)
		printf("%zu_ms %zu is compiling\n", time_ms(p, 0), p->id + 1);
	else if (state == DEBUGING)
		printf("%zu_ms %zu is debugging\n", time_ms(p, 0), p->id + 1);
	else if (state == REFACTOR)
		printf("%zu_ms %zu is refactoring\n", time_ms(p, 0), p->id + 1);
	else if (state == WAITING && dg != 'F')
		printf("%zu_ms %zu took %c dongle\n", time_ms(p, 0), p->id + 1, dg);
}

int	print_report(t_coder *p, t_data *t, char dg)
{
	int	state;

	pthread_mutex_lock(&p->mut_self);
	state = p->state;
	pthread_mutex_unlock(&p->mut_self);
	if (state != BURNOUT)
	{
		pthread_mutex_lock(&t->monitor_mut);
		if (t->stop)
		{
			pthread_mutex_unlock(&t->monitor_mut);
			return (0);
		}
		pthread_mutex_lock(&t->print_mutex);
		pthread_mutex_unlock(&t->monitor_mut);
	}
	else
		pthread_mutex_lock(&t->print_mutex);
	print_msg(p, dg, state);
	pthread_mutex_unlock(&t->print_mutex);
	return (0);
}

int	request_dongles(t_coder *p, t_data *t)
{
	pthread_mutex_lock(&t->monitor_mut);
	p->permision = 0;
	p->deadline = p->previos_compile + t->burnout_time;
	t->ready_q->push(t->ready_q, p);
	while (!p->permision && !t->stop)
		pthread_cond_wait(&p->permi_cond, &t->monitor_mut);
	if (t->stop)
	{
		pthread_mutex_unlock(&t->monitor_mut);
		return (-1);
	}
	pthread_mutex_unlock(&t->monitor_mut);
	return (0);
}
