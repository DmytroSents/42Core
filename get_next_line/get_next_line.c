/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:11:26 by dbrusent          #+#    #+#             */
/*   Updated: 2026/06/06 03:49:19 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SOFT_LIMIT 1024

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*join_w_free(char **str1, char **str2, size_t f_call)
{
	char	*temp;

	temp = NULL;
	if (f_call == 'F')
	{
		if (str1 && *str1 != NULL)
		{
			free(*str1);
			*str1 = NULL;
		}
		if (str2 && *str2 != NULL)
		{
			free(*str2);
			*str2 = NULL;
		}
	}
	if ((str1 && str2) && (*str1 && *str2) && f_call == 'J')
	{
		temp = ft_strjoin(*str1, *str2);
		free(*str1);
		*str1 = NULL;
		if (!temp)
			return (NULL);
	}
	return (temp);
}

char	*read_someline(int fd, char *maybe_buf)
{
	char	*maybe_line;
	ssize_t	bytes_read;

	bytes_read = 1;
	maybe_line = malloc(BUFFER_SIZE + 1);
	if (!maybe_line)
		return (join_w_free(NULL, &maybe_buf, 'F'));
	while (!ft_strchr(maybe_buf, '\n'))
	{
		bytes_read = read(fd, maybe_line, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read < 0)
			return (join_w_free(&maybe_line, &maybe_buf, 'F'));
		maybe_line[bytes_read] = '\0';
		maybe_buf = join_w_free(&maybe_buf, &maybe_line, 'J');
		if (!maybe_buf)
			return (join_w_free(NULL, &maybe_line, 'F'));
	}
	free(maybe_line);
	return (maybe_buf);
}

char	*get_next_line(int fd)
{
	static char	*buffer[SOFT_LIMIT];
	char		*turn_line;
	size_t		nl_pos;

	nl_pos = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > SOFT_LIMIT)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_substr("", 0, 0);
	buffer[fd] = read_someline(fd, buffer[fd]);
	if (!buffer[fd])
		return (join_w_free(NULL, &buffer[fd], 'F'));
	turn_line = substract_line(&nl_pos, buffer[fd]);
	if (!turn_line)
		return (join_w_free(NULL, &buffer[fd], 'F'));
	buffer[fd] = shift_rest_left(nl_pos, buffer[fd]);
	return (turn_line);
}

char	*substract_line(size_t *nl_chr, char *my_buffer)
{
	char	*temp_l;
	size_t	i;

	i = 0;
	temp_l = NULL;
	if (!my_buffer || !*my_buffer)
		return (NULL);
	while (my_buffer[i] && my_buffer[i] != '\n')
		i++;
	*nl_chr = i;
	if (i == ft_strlen(my_buffer))
		temp_l = malloc(i + 1);
	if (i < ft_strlen(my_buffer))
		temp_l = malloc(i + 2);
	if (!temp_l)
		return (NULL);
	ft_memcpy(temp_l, my_buffer, i);
	if (my_buffer[i] && my_buffer[i] == '\n')
		temp_l[i++] = '\n';
	temp_l[i] = '\0';
	return (temp_l);
}

char	*shift_rest_left(size_t nl_chr, char *my_buff)
{
	char	*tmp;
	size_t	b_lenght;

	b_lenght = ft_strlen(my_buff);
	if (nl_chr == b_lenght)
		return (join_w_free(&my_buff, NULL, 'F'));
	tmp = ft_substr(my_buff, nl_chr + 1, b_lenght - nl_chr);
	free(my_buff);
	return (tmp);
}

// int main(int agrc, char *argv[])
// {
// 	int		fd = open(argv[1], O_RDONLY);

// 	char *str = "";
// 	while (str)
// 	{
// 		str = get_next_line(fd);
// 		printf("is it: %s\n", str);
// 		free(str);
// 	}
// }
