/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:39:52 by aderison          #+#    #+#             */
/*   Updated: 2024/05/11 23:22:15 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_pipex(t_pipex *pipex, char *msg, int error)
{
	int	i;

	if (!pipex)
	{
		ft_putstr_fd(RED ERR_POINTER_NULL RESET, 2);
		exit(error);
	}
	i = 0;
	while (pipex->cmds && i < pipex->cmdc)
		ft_free_matrice(1, &pipex->cmds[i++]);
	if (pipex->cmds)
		free(pipex->cmds);
	if (pipex->path)
		ft_free_matrice(1, &pipex->path);
	if (msg)
		ft_putstr_fd(msg, 2);
	close(pipex->fd_input);
	close(pipex->fd_output);
	exit(error);
}
