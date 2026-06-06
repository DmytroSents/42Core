/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:17:53 by dbrusent          #+#    #+#             */
/*   Updated: 2025/11/11 16:48:41 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>
# include <stdlib.h>
# include <stdarg.h>
//# include <stdio.h>

int		ft_printf(char const *format, ...);

char	ft_strchr(char *str, int c);
int		val_spc(char *fmt, int *err_flag);

int		print_format(char fmt, va_list	arg_p);
int		ft_print_s(char *str);
int		ft_print_ptr(void *addres);

int		find_len_base(long ntemp, int base);
int		print_num_base(int num, int base);

int		print_unsigned_base(unsigned int u_num, int base, char fmt_c);

#endif
