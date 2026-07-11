/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 02:12:17 by dbrusent          #+#    #+#             */
/*   Updated: 2026/07/11 16:40:09 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

/* ./codexion {num_coders} {time2_burnout} {time2_compile} {time2_debug} 
	{time2_refactor} {num_compiles_req} {dongle_cooldown} {scheduler} 
	./codexion   6   1200   600   200   200   3   25   fifo  	*/

	#include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

int	main(int argc, char *argv[])
{
	int		i;
	t_data	p_tr;
	int		ft_errno;

	i = 0;
	ft_errno = argc;
	ft_errno = parse_args(argv, &p_tr, &ft_errno, 0);
	if (ft_errno)
		return (ft_errno);
	if (fill_struct(&p_tr) < 0)
		return (-1);

	print_stuff(&p_tr);

	if (create_threads(&p_tr, 0))
		return (ft_free(&p_tr, -3));

	ft_destroy_join(&p_tr, p_tr.coders_num, 'J');
	return (ft_free(&p_tr, 0));
}

// The scheduler is not scheduling threads;
// it is scheduling access to each dongle.
// policy decides which coder gets a dongle next.

int	time_ms(t_coder *ptr)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	ptr->elapsed = (size_t)tv.tv_sec * 1000;
	ptr->elapsed += (size_t)tv.tv_usec / 1000;
	return ((int)ptr->elapsed - ptr->time_0);
}

void	print_stuff(t_data *p)
{
	int	i;

	i = -1;
	while (++i < p->coders_num)
	{
		printf("ID:%zu; Dongle_L:%p;", p->coders[i].id, p->coders[i].left);
		printf("Dongle_R:%p\n", p->coders[i].right);
	}
	// printf("Coders_num: %zu;\n", p->coders_num);
	// printf("Burnout_time: %zu;\n", p->burnout_time);
	// printf("Compile_time: %zu;\n", p->compile_time);
	// printf("Debugin_time: %zu;\n", p->debugin_time);
	// printf("Refactor_time: %zu;\n", p->refactor_time);
	// printf("Compile_req_num: %zu;\n", p->compile_req_num);
	// printf("Dongle_cooldown: %zu\n", p->dongle_cooldown);
}
