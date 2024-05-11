/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:44:34 by aderison          #+#    #+#             */
/*   Updated: 2024/05/11 22:32:36 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*create_cmd(t_pipex pipex, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	if (!cmd)
		return (NULL);
	i = -1;
	while (pipex.path && pipex.path[++i])
	{
		tmp = ft_strjoin(pipex.path[i], "/");
		if (!tmp)
			exit_pipex(&pipex, RED ERR_POINTER_NULL RESET, EXIT_FAILURE);
		path = ft_strjoin(tmp, cmd);
		if (!path)
		{
			ft_free(1, &tmp);
			exit_pipex(&pipex, RED ERR_POINTER_NULL RESET, EXIT_FAILURE);
		}
		if (access(path, X_OK) == 0)
			return (ft_free(1, &tmp), path);
		ft_free(2, &tmp, &path);
	}
	ft_printf(MAG "pipex:" RESET "command not found: %s\n", cmd);
	return (NULL);
}
static void file(t_pipex *pipex, char *input, char *output)
{
	pipex->fd_input = open(input, O_RDONLY);
	if (pipex->fd_input < 0)
		ft_printf(MAG "pipex:" RESET " %s: %s\n", strerror(errno), input);
	pipex->fd_output = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_output < 0)
		ft_printf(MAG "pipex:" RESET " %s: %s\n", strerror(errno), output);
	if(pipex->fd_input < 0 || pipex->fd_output < 0)
		exit_pipex(pipex, NULL, EXIT_SUCCESS);
}

int	init_struct(t_pipex *pipex, char *input, char *output, char **cmds,
		int argc)
{
	int	i;

	if (!pipex || !input || !output || !cmds || !*cmds)
		return (ft_putstr_fd(RED ERR_POINTER_NULL "[+] A NULL pointer detected during init" RESET,
				2));
	pipex->cmdc = argc - 3;
	file(pipex, input, output);
	pipex->cmds = malloc(sizeof(char **) * pipex->cmdc);
	if (!pipex->cmds)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < pipex->cmdc)
		pipex->cmds[i] = ft_split(cmds[i], ' ');
	while (i-- > 0)
		pipex->cmds[i][0] = create_cmd(*pipex, pipex->cmds[i][0]);
	return (0);
}
