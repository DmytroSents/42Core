/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:32:44 by dbrusent          #+#    #+#             */
/*   Updated: 2025/12/24 12:04:11 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

int	ft_print_s_fd(int file_des, char *str)
{
	int		i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
		i++;
	return (write(file_des, str, i));
}

static char	chr_strchr(char *str, int c)
{
	while (*str && *str != (unsigned char)c)
		str++;
	if (*str == (unsigned char)c)
		return (*str);
	else
		return (0);
}

static int	val_spc(char *fmt, int *err_flag)
{
	if (*fmt == '%' && *(fmt + 1) == '\0' && !(*err_flag))
		return (-1);
	if (*fmt == '%' && *(fmt + 1) && !chr_strchr("sdiupxXc%", *(fmt + 1)))
	{
		(*err_flag)++;
		return (0);
	}
	return (chr_strchr("sdiupxXc%", *(fmt + 1)));
}

static int	print_format(char fmt, va_list	arg_p)
{
	int	write_chr;

	if (fmt == 's')
		return (ft_print_s_fd(1, va_arg(arg_p, char *)));
	else if (fmt == 'd' || fmt == 'i')
		return (print_num_base(va_arg(arg_p, int), 10));
	else if (fmt == 'u')
		return (print_unsigned_base(va_arg(arg_p, unsigned int), 10, 'u'));
	else if (fmt == 'p')
		return (ft_print_ptr(va_arg(arg_p, void *)));
	else if (fmt == 'x')
		return (print_unsigned_base(va_arg(arg_p, unsigned int), 16, 'x'));
	else if (fmt == 'X')
		return (print_unsigned_base(va_arg(arg_p, unsigned int), 16, 'X'));
	if (fmt == '%')
		return (write(1, "%", 1));
	else if (fmt == 'c')
	{
		write_chr = (char)va_arg(arg_p, int);
		return (write(1, &write_chr, 1));
	}
	return (-1);
}

int	ft_printf(const char*format, ...)
{
	va_list	arg_p;
	int		error_f;
	int		counter;
	char	*fmt_s;

	counter = 0;
	error_f = 0;
	if (format == NULL)
		return (-1);
	fmt_s = (char *)format;
	va_start(arg_p, format);
	while (*fmt_s)
	{
		if (*fmt_s == '%' && val_spc(fmt_s, &error_f) == -1 && !error_f)
			return (-1);
		else if (*fmt_s == '%' && val_spc(fmt_s, &error_f) == 0)
			counter += write(1, (fmt_s), 1);
		else if (*fmt_s == '%' && val_spc(fmt_s, &error_f) > 0)
			counter += print_format(*(++fmt_s), arg_p);
		else if (*fmt_s && *fmt_s != '%')
			counter += write(1, (fmt_s), 1);
		fmt_s++;
	}
	va_end(arg_p);
	return (counter);
}
