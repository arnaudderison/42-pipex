/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:06:55 by aderison          #+#    #+#             */
/*   Updated: 2024/05/14 15:15:34 by aderison         ###   ########.fr       */
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
		exit_pipex(&pipex, NULL, EXIT_FAILURE);
}

static void	precess(t_pipex *pipex)
{
	int		*fds;
	pid_t	pid;
	int		i;

	fds = malloc(sizeof(int) * 2 * (pipex->cmdc - 1));
	if (!fds)
		exit_pipex(pipex, RED ERR_POINTER_NULL RESET, EXIT_FAILURE);
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
	ft_free(1, &fds);
	i = -1;
	while (++i < pipex->cmdc)
		wait(NULL);
}

static void	heredoc(t_pipex *pipex, char *limiter, char *output, char **cmds)
{
	char	*line;
	int		fd;

	fd = open(HEREDOC_FILE, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		exit_pipex(pipex, RED HEREDOC_FILE RESET, EXIT_FAILURE);
	line = NULL;
	while (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0 || line == NULL)
	{
		ft_free(1, &line);
		ft_printf(" >");
		line = get_next_line(0);
		write(fd, line, ft_strlen(line));
	}
	ft_free(1, &line);
	prepare(pipex, HEREDOC_FILE, output, cmds);
	precess(pipex);
	unlink(HEREDOC_FILE);
	exit_pipex(pipex, GREEN SUCCESS_MESSAGE RESET, 0);
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
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		pipex.cmdc = argc - 4;
		heredoc(&pipex, argv[2], argv[argc - 1], argv + 3);
	}
	pipex.cmdc = argc - 3;
	prepare(&pipex, argv[1], argv[argc - 1], argv + 2);
	precess(&pipex);
	exit_pipex(&pipex, GREEN SUCCESS_MESSAGE RESET, EXIT_SUCCESS);
	return (0);
}
