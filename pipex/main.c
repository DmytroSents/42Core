/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 21:42:46 by dbrusent          #+#    #+#             */
/*   Updated: 2026/06/17 11:12:14 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	param_init(t_param **p, int argc, char *argv[], char **env)
{
	int	i;

	i = 0;
	*p = (t_param *)ft_calloc(1, sizeof(t_param));
	if (*p == NULL)
		return (-1);
	(*p)->cmd_argv = (char ***)ft_calloc((argc - 2), sizeof(char **));
	if ((*p)->cmd_argv == NULL)
		return (-1);
	while (i + 2 < argc - 1)
	{
		(*p)->in_file = ft_strtrim(argv[i + 2], "\t ");
		if ((*p)->in_file == NULL)
			return (ft_free((*p)), -1);
		(*p)->cmd_argv[i] = ft_split((*p)->in_file, ' ');
		if ((*p)->cmd_argv[i] == NULL)
			return (free((*p)->in_file), ft_free((*p)), -1);
		free((*p)->in_file);
		(*p)->in_file = NULL;
		i++;
	}
	(*p)->in_file = argv[1];
	(*p)->file_out = argv[argc - 1];
	return (get_env_path(*p, env));
}

int	main(int argc, char *argv[], char **env)
{
	t_param	*param;
	pid_t	pid[2];

	param = NULL;
	if (argc != 5)
		return (perror("Input  file1 \"cmd1\" \"cmd2\" file2  to achieve"), -1);
	if (param_init(&param, argc, argv, env) < 0)
		perror_pexit(param, EXIT_FAILURE);
	if (pipe(param->pipe_fd) < 0)
		perror_pexit(param, EXIT_FAILURE);
	pid[0] = first_fork_exe(param, env);
	if (pid[0] < 0)
		perror_pexit(param, EXIT_FAILURE);
	pid[1] = last_fork_exe(param, env);
	if (pid[1] < 0)
		perror_pexit(param, EXIT_FAILURE);
	close(param->pipe_fd[0]);
	close(param->pipe_fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	
	ft_free(param);
	return (0);
}

	// int BUFF_SIZE = 7777;	int bs = 0;
	// char	buffer[BUFF_SIZE];	while(bs<BUFF_SIZE)buffer[bs++] = 0;
	// close(param->pipe_fd[1]);
	// ssize_t n = read(param->pipe_fd[0], buffer, BUFF_SIZE - 1);
	// if (n >= 0)	buffer[n] = '\0';
	// close(param->pipe_fd[0]);
	// printf("%s\nNot in fork?\n", buffer);
	//int i = 0;while(env[i])printf("%s\n", env[i++]);