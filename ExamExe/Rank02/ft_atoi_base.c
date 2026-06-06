/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:04:52 by dbrusent          #+#    #+#             */
/*   Updated: 2026/05/10 01:31:32 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <limits.h>

static int ft_isspace(char chr)
{
	return ((chr >= 9 && chr <= 13) || chr == ' ');
}

static int	ft_strchr(const char *s, int c, int flag)
{
	size_t i = 0;
	while(s[i] && s[i] != c)
		i++;
	if (flag)
		return (i);
	return (s[i]);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int		sign = 1;	
	int		reslt = 0;
	size_t	i = 0;
	char set[2][17] = {"0123456789abcdef","0123456789ABCDEF"};

	set[0][str_base] = '\0';	set[1][str_base] = '\0';
	
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
		
	if (str[i] == '-' || str[i] == '+')
		i++;

	while(str[i] && (ft_strchr(set[0], str[i], 0) || ft_strchr(set[1], str[i], 0)))
	{
		reslt =  reslt * str_base;
		if (str[i] >= 'A' && str[i] <= 'Z')
			reslt = reslt + ft_strchr(set[1], str[i], 'Y');
		if (str[i] >= 'a' && str[i] <= 'z')
			reslt = reslt + ft_strchr(set[0], str[i], 'Y');	
		i++;
	}
	
	return (reslt * sign);
}

int main(void)
{
	printf("%d\n", ft_atoi_base("6a7dfE", 16));
	printf("%d\n", INT_MAX);
}


// int mini_atoi(char *str)
// {
// 	int		sign = 1;
// 	int		reslt = 0;
// 	size_t	i = 0;
// 	char	*set = "0123456789";

// 	while (ft_isspace(str[i]))
// 		i++;
// 	if (str[i] == '-')
// 		sign = -1;
// 	if (str[i] == '-' || str[i] == '+')
// 		i++;

// 	while(str[i] && ft_strchr(set, str[i], 0))
// 	{
// 		reslt =  reslt * 10 + ft_strchr(set, str[i], 'Y');
// 		i++;
// 	}
// 	return (reslt * sign);
// }