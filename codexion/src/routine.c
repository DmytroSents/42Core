/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 10:56:11 by dbrusent          #+#    #+#             */
/*   Updated: 2026/07/13 06:19:15 by dbrusent         ###   ########.fr       */
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
	time_ms(p, "time_0");
	while (p->state && p->comp_todo)
	{
		// if (!request_dongles(p, p->data))
		// 	continue ;
		compile(p, p->data);
		p->state = DEBUGING;
		print_report(p, p->data);
		usleep((p->data->debugin_time) * 1000);
		p->state = REFACTOR;
		print_report(p, p->data);
		usleep((p->data->refactor_time) * 1000);
		p->state = WAITING;
		if (p->comp_todo == 0)
		{	pthread_mutex_lock(p->data->print_mutex);
			printf("%dms " GREEN "%zu " RESET "has ", time_ms(p, 0), p->id);
			printf(GREEN "finished " RESET "simulation"  "\n");
			pthread_mutex_unlock(p->data->print_mutex);	}
	}
	return (NULL);
}

int	compile(t_coder *p, t_data *t)
{
	pthread_mutex_lock(&p->left->ptr);
	pthread_mutex_lock(&p->right->ptr);
	print_report(p, t);
	time_ms(p, "time_0");
	p->state = COMPILNG;
	print_report(p, t);
	usleep((p->data->compile_time) * 1000);
	p->comp_todo = p->comp_todo - 1;
	pthread_mutex_unlock(&p->left->ptr);
	pthread_mutex_unlock(&p->right->ptr);
	//t->
	return (0);
}

int	print_report(t_coder *p, t_data *t)
{
	int		i;

	i = -1;
	pthread_mutex_lock(t->print_mutex);
	if (p->state == COMPILNG)
		i = printf("%dms %zu is compiling\n", time_ms(p, 0), p->id);
	else if (p->state == DEBUGING)
		i = printf("%dms %zu is debugging\n", time_ms(p, 0), p->id);
	else if (p->state == REFACTOR)
		i = printf("%dms %zu is refactoring\n", time_ms(p, 0), p->id);
	else if (p->state == WAITING)
		i = printf("%dms %zu has taken both dongles\n", time_ms(p, 0), p->id);
	pthread_mutex_unlock(t->print_mutex);
	return (i);
}

void	*monitor(void *data)
{
	t_data	*ptr;

	ptr = (t_data *)data;
	//printf("This bitch is dead!");
	return (NULL);
}

int	request_dongles(t_coder *cod, t_data *dat)
{
	return (0);
}
