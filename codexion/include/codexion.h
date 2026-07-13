/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 02:27:41 by dbrusent          #+#    #+#             */
/*   Updated: 2026/07/13 06:19:33 by dbrusent         ###   ########.fr       */
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
# include "utils.h"
# include <limits.h>

# define READY 1
# define ON_CD 0

# define GREEN "\033[32m"
# define RESET "\033[0m"
# define BOLD_GREEN "\033[1;32m"

typedef struct s_data	t_data;
typedef struct s_coder	t_coder;
typedef struct s_dongle	t_dongle;

typedef enum state
{
	BURNOUT,
	COMPILNG,
	DEBUGING,
	REFACTOR,
	WAITING,
}	t_state;

struct s_dongle
{
	int				state;
	pthread_mutex_t	ptr;
	size_t			release_time;
};

struct s_coder
{
	size_t			id;
	t_data			*data;
	int				state;
	pthread_t		thread;
	size_t			comp_todo;
	t_dongle		*right;	
	t_dongle		*left;
	size_t			time_0;
	size_t			elapsed;
};

struct s_data
{
	t_coder			*coders;
	t_dongle		*dongle;
	size_t			coders_num;
	size_t			burnout_time;
	size_t			compile_time;
	size_t			debugin_time;
	size_t			refactor_time;
	size_t			compile_req_num;
	size_t			dongle_cooldown;
	pthread_mutex_t	*print_mutex;
};

int		time_ms(t_coder *ptr, char *str);
void	*monitor(void *data);
void	*routine(void *coder);
int		compile(t_coder *p, t_data *t);

int		print_report(t_coder *p, t_data *t);
int		request_dongles(t_coder *cod, t_data *dat);

/* ./codexion {num_coders} {time2_burnout} {time2_compile} {time2_debug} 
	{time2_refactor} {num_compiles_req} {dongle_cooldown} {scheduler} 
	./codexion   6   1200   600   200   200   3   25   fifo  	*/

#endif
