/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:06:55 by aderison          #+#    #+#             */
/*   Updated: 2024/05/11 21:59:21 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_null(t_pipex *pipex)
{
	pipex->cmds = NULL;
	pipex->path = NULL;
}

static void	execute_command(t_pipex pipex, int fds[], int i)
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
	j = -1;
	while (++j < 2 * (pipex.cmdc - 1))
		close(fds[j]);
	if (execve(pipex.cmds[i][0], pipex.cmds[i], pipex.path) == -1)
	{
		ft_printf(MAG "pepex:" RESET " %s: ", strerror(errno));
		exit_pipex(&pipex, "null", EXIT_FAILURE);
	}
}

static void	precess(t_pipex *pipex)
{
	int		fds[2 * (pipex->cmdc - 1)];
	pid_t	pid;
	int		i;

	ft_create_pipes(fds, pipex->cmdc);
	i = -1;
	while (++i < pipex->cmdc)
	{
		pid = fork();
		if (pid < 0)
			exit_pipex(pipex, RED "Fork error (pid < 0)" RESET, EXIT_FAILURE);
		if (pid == 0)
			execute_command(*pipex, fds, i);
	}
	ft_close_pipes(fds, pipex->cmdc);
	i = -1;
	while (++i < pipex->cmdc)
		wait(NULL);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc < 5 || !argv || !*argv)
		return (ft_putstr_fd(RED NB_ARGS_ERR RESET, 2));
	if (!env || !(*env))
		return (ft_putstr_fd(RED ENV_ERR RESET, 2));
	init_null(&pipex);
	pipex.path = path_exist(env);
	if (!pipex.path || !(*pipex.path))
		return (ft_putstr_fd(RED ENV_ERR RESET, 2));
	init_struct(&pipex, argv[1], argv[argc - 1], argv + 2, argc);
	precess(&pipex);
	exit_pipex(&pipex,
		GREEN "\nPipex Terminé avec succès. \nBy Arnaud Derison (aderison)" RESET,
		EXIT_SUCCESS);
	return (0);
}
