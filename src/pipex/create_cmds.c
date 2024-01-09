/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnaud <arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 09:17:46 by arnaud            #+#    #+#             */
/*   Updated: 2024/01/08 23:30:49 by arnaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static void	myError(int error, char *title, char *msg)
{
	if (error == ENOENT)
	{
		ft_putstr_fd(title, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
}

char	**create_cmds(char ***s_cmds, int size, char **env)
{
	char	**cmds;
	int		i;
	char	*tmp;

	cmds = (char **)malloc(sizeof(char *) * (size + 1));
	i = -1;
	while (s_cmds[++i] && i < size)
	{
		tmp = ft_strdup(s_cmds[i][0]);
		if (!tmp)
			return (ft_free_matrice(1, &cmds), NULL);
		cmds[i] = find_path(tmp, env);
		if (!cmds[i])
			return (ft_free_matrice(1, &cmds), myError(ENOENT, tmp, NFCMD),
				NULL);
		ft_free(1, &tmp);
	}
	cmds[i] = NULL;
	return (cmds);
}
