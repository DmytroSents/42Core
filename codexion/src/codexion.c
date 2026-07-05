/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 02:12:17 by dbrusent          #+#    #+#             */
/*   Updated: 2026/07/05 08:47:52 by dbrusent         ###   ########.fr       */
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
	t_data	p_tr;
	int		ft_errno;

	ft_errno = argc;
	ft_errno = parse_args(argv, &p_tr, &ft_errno, 0);
	if (ft_errno)
		return (ft_errno);
	if (fill_struct(&p_tr) < 0)
		return (-1);

	ft_errno = (int)errno;
	printf("\nFT_ERR:%d;\n", ft_errno);
	printf("SizeOfT_Data:%zu\n", sizeof(t_data));
	if (create_threads(&p_tr, 0) != 0)
		return (-1);
	int i = 0;
	while (i < p_tr.coders_num)
	{
		if (pthread_join(p_tr.coders[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (ft_free(&p_tr, 0));
}

// The scheduler is not scheduling threads;
// it is scheduling access to each dongle.
// policy decides which coder gets a dongle next.
int create_threads(t_data *p, int i)
{
	while (i < p->coders_num)
	{
		if (pthread_create(&p->coders[i].thread, NULL, &routine, &p->coders[i]))
			return (-1);
		i++;
	}
	return (0);
}
void	*routine(void *coder)
{
	t_coder	*ptr;

	ptr = (t_coder *)coder;
	printf("ID:%zu\n", ptr->id);
	// request dongle ? compile : die
	// release dongles
	// debug -> refactor
	// wrap it inside while (lo0p)
	// change state_variables every step
	// implement time-functions
	return (NULL);
}