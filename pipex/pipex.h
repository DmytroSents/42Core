/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 12:26:52 by dbrusent          #+#    #+#             */
/*   Updated: 2026/06/13 12:43:04 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

/*STDIN_FILENO 0	STDOUT_FILENO 1		STDERR_FILENO 2		<unistd.h>*/

typedef struct param
{
	int			fd[5];		//???
	int			pipe_fd[2];
	char		**path_v;
	char		***cmd_argv;
	char		*in_file;
	char		*file_out;
}				t_param;

void	ft_free(t_param	*p);
int		param_init(t_param **p, int argc, char *argv[], char **env);

int		get_env_path(t_param *p, char **envp);
char	*ft_full_path(t_param *p, char **envp, int n);

pid_t	first_fork_exe(t_param *p, char **env);
pid_t	last_fork_exe(t_param *p, char **env);

void	perror_pexit(t_param *p, int num);

#endif
