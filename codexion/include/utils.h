/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 02:40:28 by dbrusent          #+#    #+#             */
/*   Updated: 2026/07/05 04:46:19 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "codexion.h"

typedef struct s_data	t_data;
typedef struct s_coder	t_coder;

void	print_stuff(t_data *p);
int		fill_struct(t_data *p);

int		ft_free(t_data *p, int ex_code);

int		parse_args(char *argv[], t_data	*p, int *ft_err, int i);

#endif
