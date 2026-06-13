/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 06:47:54 by dbrusent          #+#    #+#             */
/*   Updated: 2026/06/13 10:36:35 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_env_path(t_param *p, char **env)
{
	int		i;
	int		j;
	size_t	s_len;
	char	*std_path;

	i = 0;
	j = 0;
	while (j < 5)
		p->fd[j++] = -1;
	while (env[i])
	{
		if (ft_memcmp("PATH=", env[i], 5) == 0)
			break ;
		i++;
	}
	s_len = ft_strlen(env[i]);
	if (s_len <= 5)
		std_path = "/usr/local/bin:/usr/bin:/bin";
	if (s_len > 5)
		std_path = env[i] + 5;
	p->path_v = ft_split(std_path, ':');
	if (p->path_v == NULL)
		return (-1);
	return (0);
}

char	*ft_full_path(t_param *p, char **envp, int n)
{
	int		s;
	size_t	len[2];
	char	*temp;

	s = 0;
	temp = NULL;
	if (!p->path_v || !p->cmd_argv || !p->cmd_argv[n])
		return (NULL);
	while (p->path_v[s])
	{
		len[0] = ft_strlen(p->path_v[s]);
		len[1] = ft_strlen(p->cmd_argv[n][0]);
		temp = ft_calloc(len[0] + len[1] + 2, 1);
		if (!temp)
			return (NULL);
		ft_memcpy(temp, p->path_v[s], len[0]);
		temp[len[0]] = '/';
		ft_memcpy(temp + len[0] + 1, p->cmd_argv[n][0], len[1]);
		if (access(temp, X_OK) == 0)
			return (temp);
		free(temp);
		s++;
	}
	return (NULL);
}

void	ft_free(t_param	*p)
{
	int	i;

	i = 0;
	if (p == NULL)
		return ;
	while (p->cmd_argv[i] != NULL)
	{
		free_split(p->cmd_argv[i], 'f');
		i++;
	}
	if (p->path_v)
		free_split(p->path_v, 'f');
	if (p->cmd_argv)
		free(p->cmd_argv);
	free(p);
}

void	perror_pexit(t_param *p, int num)
{
	perror(NULL);
	ft_free(p);
	exit(1);
}