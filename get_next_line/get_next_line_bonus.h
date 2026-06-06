/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:11:42 by dbrusent          #+#    #+#             */
/*   Updated: 2025/12/03 18:31:04 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 77
# endif

# include <unistd.h>
# include <stddef.h>
# include <stdint.h>
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_substr(char const *str, size_t start, size_t len);

int		ft_memsetzero(size_t *some_counter, char **bafer);
char	*join_w_free(char **str1, char **str2, size_t f_call);

char	*read_someline(int fd, char *maybe_buf);

char	*substract_line(size_t *nl_chr, char *my_buffer);
char	*shift_rest_left(size_t nl_chr, char *my_buff);

#endif
