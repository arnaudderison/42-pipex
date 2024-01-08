/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnaud <arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:05:22 by arnaud            #+#    #+#             */
/*   Updated: 2024/01/09 00:32:13 by arnaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	close_pipes(int fds[], int cmdc)
{
	int	i;

	i = 0;
	while (i < 2 * (cmdc - 1))
	{
		close(fds[i]);
		i++;
	}
}

static void	create_pipes(int fds[], t_pipex pipex)
{
	int	i;

	i = 0;
	while (i < pipex.cmdc - 1)
	{
		if (pipe(fds + i * 2) < 0)
			exit_pipex(&pipex, "pipe error");
		i++;
	}
}

static void	execute_command(t_pipex pipex, int fds[], int i, char **env)
{
	int	j;

	if (i == 0)
		dup2(pipex.fd_input, 0);
	else
		dup2(fds[(i - 1) * 2], 0);
	if (i == pipex.cmdc - 1)
		dup2(pipex.fd_output, 1);
	else
		dup2(fds[i * 2 + 1], 1);
	j = 0;
	while (j < 2 * (pipex.cmdc - 1))
	{
		close(fds[j]);
		j++;
	}
	if (execve(pipex.cmds[i], pipex.s_cmds[i], env) == -1)
	{
		perror(pipex.cmds[i]);
		exit_pipex(&pipex, "Error cve");
	}
}

static void	process(t_pipex pipex, char **env)
{
	int		fds[2 * (pipex.cmdc - 1)];
	int		i;
	pid_t	pid;

	create_pipes(fds, pipex);
	i = 0;
	while (i < pipex.cmdc)
	{
		pid = fork();
		if (pid == 0)
			execute_command(pipex, fds, i, env);
		else if (pid < 0)
			exit_pipex(&pipex, "Fork error");
		i++;
	}
	close_pipes(fds, pipex.cmdc);
	i = -1;
	while (++i < pipex.cmdc)
		wait(NULL);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc < 5 || !argv)
		return (ft_putstr_fd(RED NB_ARGS_ERR RESET, 2));
	if (!env)
		return (ft_putstr_fd(RED NO_ENV_ERR RESET, 2));
	init(&pipex, argv, env, argc);
	process(pipex, env);
	close(pipex.fd_input);
	close(pipex.fd_output);
	return (1);
}
