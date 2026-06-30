/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 02:12:17 by dbrusent          #+#    #+#             */
/*   Updated: 2026/06/30 09:45:36 by dbrusent         ###   ########.fr       */
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
	// if (ft_errno) return (ft_errno);

	ft_errno = (int)errno;
	printf("\nFT_ERR:%d;\n", ft_errno);
	return (0);
}

int	parse_args(char *argv[], t_data	*p, int *ft_err, int i)
{
	int	arg_i[7];

	if (*ft_err != 9)
		return (9);
	if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
		return (8);
	memset(arg_i, 0, 7 * sizeof(int));
	while (++i < 8)
	{
		*ft_err = 0;
		arg_i[i - 1] = atoi(argv[i]);
		if (arg_i[i - 1] <= 0)
			return (i);
	}
	p->coders_num = (size_t)(arg_i[0] + 1);
	p->coders = malloc(sizeof(t_coder) * (p->coders_num));
	if (p->coders == NULL)
		return (-1);
	p->burnout_time = (size_t)arg_i[1];
	p->compile_time = (size_t)arg_i[2];
	p->debugin_time = (size_t)arg_i[3];
	p->refactor_time = (size_t)arg_i[4];
	p->compile_req_num = (size_t)arg_i[5];
	p->dongle_cooldown = (size_t)arg_i[6];
	return (*ft_err);
}

int	fill_struct(t_data *p)
{
	int	i;

	i = 0;
	while (i < p->coders_num)
	{
		p->coders[i].data = p;
		p->coders[i].id = i++;
	}
}
