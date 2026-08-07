/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 02:40:28 by dbrusent          #+#    #+#             */
/*   Updated: 2026/08/05 20:10:54 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "codexion.h"

typedef struct s_data	t_data;
typedef struct s_coder	t_coder;
typedef struct s_dongle	t_dongle;
typedef struct s_queue	t_queue;

struct				s_queue
{
	t_coder			**arr;
	size_t			rear;
	size_t			count;
	size_t			front;
	size_t			capacity;
	t_coder			*(*pop)(struct s_queue *);
	int				(*push)(struct s_queue *, t_coder *);
};

int		ft_strisnum(char *str);
ssize_t	time_ms(t_coder *ptr, char *str);

int		queue_init(t_data *p, t_queue *q);
int		fifo_push(t_queue *qu, t_coder *p);
int		edf_insert(t_queue *qu, t_coder *p);
t_coder	*fifo_pop(t_queue *qu);
t_coder	*edf_extract(t_queue *qu);

int		ft_free(t_data *p, t_queue *q, int ex_code);

int		create_threads(t_data *p, int i);
int		ft_destroy_join(t_data *p, int amount, char chr);

int		print_report(t_coder *p, t_data *t, char dg);

#endif
