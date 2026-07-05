/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 02:27:41 by dbrusent          #+#    #+#             */
/*   Updated: 2026/07/05 07:38:21 by dbrusent         ###   ########.fr       */
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
# include "ft_threads.h"
# include <limits.h>

# define READY 1
# define ON_CD 0

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

struct s_coder
{
	size_t			id;
	int				state;
	pthread_t		thread;
	size_t			comp_todo;
	pthread_mutex_t	*right;	
	pthread_mutex_t	*left;
	t_data			*data;
};

struct s_data
{
	t_coder			*coders;
	size_t			coders_num;
	size_t			burnout_time;
	size_t			compile_time;
	size_t			debugin_time;
	size_t			refactor_time;
	size_t			compile_req_num;
	size_t			dongle_cooldown;
	pthread_mutex_t	*dongles;
};

void	*routine(void *coder);
int		create_threads(t_data *p, int i);

/* ./codexion {num_coders} {time2_burnout} {time2_compile} {time2_debug} 
	{time2_refactor} {num_compiles_req} {dongle_cooldown} {scheduler} 
	./codexion   6   1200   600   200   200   3   25   fifo  	*/

#endif
