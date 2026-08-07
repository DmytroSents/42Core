/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 10:56:11 by dbrusent          #+#    #+#             */
/*   Updated: 2026/08/06 18:59:48 by dbrusent         ###   ########.fr       */
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
	pthread_mutex_lock(&p->data->print_mutex);
	pthread_mutex_unlock(&p->data->print_mutex);
	p->last_compile = p->data->time_0;
	while (p->state && p->comp_todo)
	{
		// while (!request_dongles(p, p->data))
		// 	 ;
		compile(p, p->data);
		if (p->comp_todo == 0)
		{
			pthread_mutex_lock(&p->data->print_mutex);
			printf("%zums " GREEN "%zu " RESET "has ", time_ms(p, 0), p->id);
			printf(GREEN "finished " RESET "simulation\n");
			pthread_mutex_unlock(&p->data->print_mutex);
			break ;
		}
		pthread_mutex_lock(&p->mut_self);
		p->state = DEBUGING;
		pthread_mutex_unlock(&p->mut_self);
		print_report(p, p->data, 0);
		usleep((p->data->debugin_time) * 1000);
		pthread_mutex_lock(&p->mut_self);
		p->state = REFACTOR;
		pthread_mutex_unlock(&p->mut_self);
		print_report(p, p->data, 0);
		usleep((p->data->refactor_time) * 1000);
		pthread_mutex_lock(&p->mut_self);
		p->state = WAITING;
		pthread_mutex_unlock(&p->mut_self);
	}
	return (NULL);
}

int	compile(t_coder *p, t_data *t)
{
	pthread_mutex_lock(&p->left->ptr);
	print_report(p, t, 'L');
	pthread_mutex_lock(&p->right->ptr);
	print_report(p, t, 'R');
	time_ms(p, "last_");
	pthread_mutex_lock(&p->mut_self);
	p->state = COMPILNG;
	pthread_mutex_unlock(&p->mut_self);
	print_report(p, t, 0);
	usleep((p->data->compile_time) * 1000);
	p->comp_todo = p->comp_todo - 1;
	pthread_mutex_unlock(&p->left->ptr);
	pthread_mutex_unlock(&p->right->ptr);
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

void	*monitor(void *data)
{
	t_data	*ptr;

	ptr = (t_data *)data;
	return (NULL);
}
