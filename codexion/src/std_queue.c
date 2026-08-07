/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 13:02:07 by dbrusent          #+#    #+#             */
/*   Updated: 2026/08/06 18:32:28 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	queue_init(t_data *p, t_queue *q)
{
	if (!q || !p)
		return (0);
	q->arr = NULL;
	q->arr = (t_coder **)malloc((p->coders_num) * sizeof(t_coder *));
	// memset 0
	if (!q->arr)
		return (-1);
	q->rear = 0;
	q->count = 0;
	q->front = 0;
	q->capacity = p->coders_num;
	return (0);
}

t_coder	*fifo_pop(t_queue *qu)
{
	t_coder	*curr;

	if (!qu || qu->count <= 0)
		return (NULL);
	curr = qu->arr[qu->front];
	qu->front = (qu->front + 1) % qu->capacity;
	qu->count--;
	return (curr);
}

/* %(modulo) operator works like this:
	rear = 0  (rear + 1) % 5 = 1
	rear = 1  (rear + 1) % 5 = 2
	rear = 2  (rear + 1) % 5 = 3
	rear = 3  (rear + 1) % 5 = 4
  rear = 4  (rear + 1) % 5 = 0   <-- wraps around*/

int	fifo_push(t_queue *qu, t_coder *p)
{
	if (!qu || qu->count == qu->capacity)
		return (-1);
	qu->arr[qu->rear] = p;
	qu->rear = (qu->rear + 1) % qu->capacity;
	qu->count++;
	return (0);
}

/*Compare the added element with its parent; if they are in the correct order,
  stop. If not, swap the element with its parent and return to the prev step.
  EDF means that the childest deadline is in root.(for max-heap change < sign)*/

int	edf_insert(t_queue *qu, t_coder *p)
{
	size_t	parent;
	size_t	current;
	t_coder	*temp;

	if (!qu || qu->count == qu->capacity)
		return (-1);
	current = qu->count;
	qu->arr[qu->count] = p;
	qu->count++;
	while (current)
	{
		parent = (current - 1) / 2;
		if (qu->arr[current]->last_compile < qu->arr[parent]->last_compile)
		{
			temp = qu->arr[parent];
			qu->arr[parent] = qu->arr[current];
			qu->arr[current] = temp;
			current = parent;
		}
		else
			break ;
	}
	return (0);
}

/*	Replace the root of the heap with the last element.
Compare the new root with its children; if they are in the correct order, stop.
If not, swap the element with one of its children and return to the previ step. 
(Swap with its childer child in a min-heap and its larger child in a max-heap)*/

t_coder	*edf_extract(t_queue *qu)
{
	size_t	i;
	t_coder	*tmp;
	t_coder	*min_deadline;
	size_t	child;

	if (!qu || qu->count == 0)
		return (NULL);
	min_deadline = qu->arr[0];
	qu->arr[0] = qu->arr[--qu->count];
	i = 0;
	while ((i * 2) + 1 < qu->count)
	{
		child = (i * 2) + 1;
		if (child + 1 < qu->count
			&& qu->arr[child + 1]->last_compile < qu->arr[child]->last_compile)
			child++;
		if (qu->arr[i]->last_compile <= qu->arr[child]->last_compile)
			break ;
		tmp = qu->arr[i];
		qu->arr[i] = qu->arr[child];
		qu->arr[child] = tmp;
		i = child;
	}
	return (min_deadline);
}
