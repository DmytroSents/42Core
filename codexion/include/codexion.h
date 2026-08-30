/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 02:27:41 by dbrusent          #+#    #+#             */
/*   Updated: 2026/08/09 20:04:43 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define GREEN "\033[32m"
# define RESET "\033[0m"
# define BOLD_GREEN "\033[1;32m"

typedef struct s_data	t_data;
typedef struct s_queue	t_queue;
typedef struct s_coder	t_coder;
typedef struct s_dongle	t_dongle;

typedef enum e_state
{
	BURNOUT,
	COMPILNG,
	DEBUGING,
	REFACTOR,
	WAITING,
}	t_state;

typedef enum e_dongle_state
{
	READY,
	IN_USE,
	COOLDOWN,
}	t_dongle_state;

struct				s_dongle
{
	int				state;
	size_t			release_time;
};

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

struct				s_coder
{
	size_t			id;
	t_data			*data;
	int				state;
	pthread_mutex_t	mut_self;
	size_t			comp_todo;
	int				permision;
	pthread_cond_t	permi_cond;
	t_dongle		*right;
	t_dongle		*left;
	pthread_t		thread;
	size_t			deadline;
	size_t			previos_compile;

};

struct				s_data
{
	int				stop;
	size_t			time_0;
	t_queue			*ready_q;
	t_coder			*coders;
	t_dongle		*dongle;
	size_t			coders_num;
	size_t			burnout_time;
	size_t			compile_time;
	size_t			debugin_time;
	size_t			refactor_time;
	size_t			compile_req_num;
	size_t			dongle_cooldown;
	pthread_t		monitor;
	char			*scheduler;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	monitor_mut;
	pthread_cond_t	monitor_cond;
};

void	*routine(void *coder);
void	broadcast_all(t_data *data);
void	*monitor(void *data);
int		check_burnout(t_data *data, size_t now, size_t i, int done);
void	scheduler(t_data *data, size_t now, size_t i, size_t total);
int		compile(t_coder *p, t_data *t);

int		fill_struct(t_data *p);
int		print_stuff(t_data *p, int error);
int		parse_args(char *argv[], t_data	*p, int *ft_err, int i);

void	do_action(t_coder	*p, int act);
int		request_dongles(t_coder *p, t_data *t);
int		print_report(t_coder *p, t_data *t, char dg);

int		ft_strisnum(char *str);
ssize_t	time_ms(t_coder *ptr, char *str);
void	sleep_partial(t_coder *p, size_t ms);
int		is_stopped(t_data *data);

int		queue_init(t_data *p, t_queue *q);
int		fifo_push(t_queue *qu, t_coder *p);
int		edf_insert(t_queue *qu, t_coder *p);
t_coder	*fifo_pop(t_queue *qu);
t_coder	*edf_extract(t_queue *qu);
t_coder	*queue_peek(t_queue *qu, char *schedul);

int		ft_free(t_data *p, t_queue *q, int ex_code);
int		create_threads(t_data *p, size_t i);
int		ft_destroy_join(t_data *p, size_t amount, char chr, size_t j);

/* ./codexion {num_coders} {time2_burnout} {time2_compile} {time2_debug}
	{time2_refactor} {num_compiles_req} {dongle_cooldown} {scheduler}
	./codexion   6   1200   600   200   200   3   25   fifo  	*/

#endif
