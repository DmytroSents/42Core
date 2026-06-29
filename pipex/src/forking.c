/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 05:49:33 by dbrusent          #+#    #+#             */
/*   Updated: 2026/06/28 06:22:37 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	first_fork_exe(t_param *p, char **env)
{
	char	*path;
	pid_t	procid;

	procid = fork();
	if (procid < 0)
		return (-1);
	if (procid == 0)
	{
		close(p->pipe_fd[0]);
		p->fd[0] = open(p->in_file, O_RDONLY);
		if (p->fd[0] < 0)
			perror_pexit(p, EXIT_FAILURE);
		if (dup2(p->fd[0], STDIN_FILENO) < 0)
			perror_pexit(p, EXIT_FAILURE);
		if (dup2(p->pipe_fd[1], STDOUT_FILENO) < 0)
			perror_pexit(p, EXIT_FAILURE);
		close(p->fd[0]);
		close(p->pipe_fd[1]);
		path = ft_full_path(p, NULL, 0);
		if (!path)
			perror_pexit(p, EXIT_FAILURE);
		execve(path, p->cmd_argv[0], env);
		perror_pexit(p, EXIT_FAILURE);
	}
	return (procid);
}

pid_t	last_fork_exe(t_param *p, char **env)
{
	char	*path;
	pid_t	procid;

	procid = fork();
	if (procid < 0)
		return (-1);
	if (procid == 0)
	{
		close(p->pipe_fd[1]);
		p->fd[1] = open(p->file_out, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (p->fd[1] < 0)
			perror_pexit(p, EXIT_FAILURE);
		if (dup2(p->pipe_fd[0], STDIN_FILENO) < 0)
			perror_pexit(p, EXIT_FAILURE);
		if (dup2(p->fd[1], STDOUT_FILENO) < 0)
			perror_pexit(p, EXIT_FAILURE);
		close(p->fd[1]);
		close(p->pipe_fd[0]);
		path = ft_full_path(p, NULL, 1);
		if (!path)
			perror_pexit(p, EXIT_FAILURE);
		execve(path, p->cmd_argv[1], env);
		perror_pexit(p, EXIT_FAILURE);
	}
	return (procid);
}
