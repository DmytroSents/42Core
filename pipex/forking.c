/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 05:49:33 by dbrusent          #+#    #+#             */
/*   Updated: 2026/06/13 15:28:42 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	first_fork_exe(t_param *p, char **env)
{
	pid_t	procid;

	procid = fork();
	if (procid < 0)
		return (-1);
	if (procid == 0)
	{
		p->fd[0] = open(p->in_file, O_RDONLY);
		if (p->fd[0] < 0)
			perror_pexit(p, 1);
		//close(p->pipe_fd[0]);
		// if (dup2(p->fd[0], STDIN_FILENO) < 0)
		// 	perror_pexit(p, 1);
		// if (dup2(p->pipe_fd[0], STDOUT_FILENO) < 0)
		// 	perror_pexit(p, 1);
		execve(ft_full_path(p, env, 0), p->cmd_argv[0], env);

		perror_pexit(p, 0);
	}
	return (procid);
}

pid_t	last_fork_exe(t_param *p, char **env)
{
		pid_t	procid;

	procid = fork();
	if (procid < 0)
		return (-1);
	if (procid == 0)
	{
		p->fd[1] = open(p->file_out, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (p->fd[1] < 0)
			perror_pexit(p, 1);
		//close(p->pipe_fd[1]);
		// if (dup2(p->fd[1], STDOUT_FILENO) < 0)
		// 	perror_pexit(p, 1);
		// if (dup2(p->pipe_fd[1], STDIN_FILENO) < 0)
		// 	perror_pexit(p, 1);
		execve(ft_full_path(p, env, 1), p->cmd_argv[1], env);

		perror_pexit(p, 0);
	}
	return (procid);
}
