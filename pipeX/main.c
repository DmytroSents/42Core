/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 21:42:46 by dbrusent          #+#    #+#             */
/*   Updated: 2026/06/13 12:45:31 by dbrusent         ###   ########.fr       */
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

	param = NULL;
	if (argc != 5)return
		(perror("Input  file1 \"cmd1\" \"cmd2\" file2  to achieve"), -1);
	if (param_init(&param, argc, argv, env) < 0)
		if (param)
			return (ft_free(param), -1);
	param->pipe_fd[1] = dup(1);
	param->pipe_fd[0] = dup(0);
	if (pipe(param->pipe_fd) < 0)
		return (ft_free(param), -1);
	first_fork_exe(param, env);
	last_fork_exe(param, env);

	ft_free(param);
	return (0);
}




