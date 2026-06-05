/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 11:46:09 by dbrusent          #+#    #+#             */
/*   Updated: 2025/12/24 12:55:06 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

//# include <stdio.h>

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <stddef.h>
# include <stdarg.h>

typedef struct t_list
{
	int				value;
	int				index;
	int				radix;
	struct t_list	*next;
}	t_list;

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int c);

char	**ft_split(char const *src, char c);
char	**ft_free_arr(char **str_arr, int amount);
int		ft_count_substr(const char *str, char c);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *str, size_t start, size_t len);

t_list	*ft_lstnew(int numb, int indx);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);

int		ft_printf(const char*format, ...);
int		ft_print_ptr(void *addres);
int		ft_print_s_fd(int file_des, char *str);
int		print_num_base(int num, int base);
int		print_unsigned_base(unsigned int u_num, int base, char fmt_c);

t_list	*ft_free_all(char **str_arr, t_list **lst_start, int i, int fflag);

#endif
