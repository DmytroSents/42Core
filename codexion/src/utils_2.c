/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 19:32:42 by dbrusent          #+#    #+#             */
/*   Updated: 2026/08/09 19:43:46 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	ft_free(t_data *p, t_queue *q, int ex_code)
{
	if (p == NULL)
		return (-1);
	if (q)
		free(q->arr);
	if (p->coders)
		free(p->coders);
	if (p->dongle)
		free(p->dongle);
	return (ex_code);
}
