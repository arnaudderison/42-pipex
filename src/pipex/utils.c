/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnaud <arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:50:56 by arnaud            #+#    #+#             */
/*   Updated: 2024/01/09 00:10:16 by arnaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static void	init_struct(t_pipex *pipex, char **argv, int argc)
{
	pipex->cmds = NULL;
	pipex->s_cmds = NULL;
	pipex->cmdc = argc - 3;
	pipex->fd_input = -1;
	pipex->fd_output = -1;
	pipex->fd_input = open(argv[1], O_RDONLY);
	if (pipex->fd_input == -1)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	pipex->fd_output = open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (pipex->fd_output == -1)
	{
		perror(argv[argc - 1]);
		exit(EXIT_FAILURE);
	}
}

static void	close_fd(t_pipex *pipex)
{
	if (pipex->fd_input)
		if (close(pipex->fd_input) == -1)
			perror("Input close Error");
	if (pipex->fd_output)
		if (close(pipex->fd_output) == -1)
			perror("Output close Error");
}

void	exit_pipex(t_pipex *pipex, char *msg)
{
	int	i;
	int	j;

	i = 0;
	if (pipex->cmds)
	{
		while (pipex->cmds[i])
			free(pipex->cmds[i++]);
		free(pipex->cmds);
	}
	i = 0;
	if (pipex->s_cmds)
	{
		while (i < pipex->cmdc && pipex->s_cmds[i])
		{
			j = 0;
			while (pipex->s_cmds[i][j])
				free(pipex->s_cmds[i][j++]);
			free(pipex->s_cmds[i++]);
		}
		free(pipex->s_cmds);
	}
	close_fd(pipex);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	init(t_pipex *pipex, char **argv, char **env, int argc)
{
	if (!pipex || !argv || !env)
		exit_pipex(pipex, NULL_PTR);
	init_struct(pipex, argv, argc);
	pipex->s_cmds = cleantab(argv, pipex->cmdc);
	if (!pipex->s_cmds)
		exit_pipex(pipex, NULL_PTR);
	pipex->cmds = create_cmds(pipex->s_cmds, pipex->cmdc, env);
	if (!pipex->cmds)
		exit_pipex(pipex, "");
}
