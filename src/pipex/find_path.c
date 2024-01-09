/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnaud <arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:44:35 by arnaud            #+#    #+#             */
/*   Updated: 2024/01/08 21:59:32 by arnaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static char	**search_path_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (ft_strnstr(env[i], "PATH", 4))
			break ;
	if (!env[i])
		return (NULL);
	return (ft_split(env[i] + 5, ':'));
}

static char	*find_bin(char **paths, char *cmd)
{
	char	*tmp;
	char	*path;
	int		i;

	if (!paths || !cmd)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (ft_free_matrice(1, &paths), NULL);
		path = ft_strjoin(tmp, cmd);
		if (!path)
			return (ft_free_matrice(1, &paths), ft_free(1, &tmp), NULL);
		if (access(path, R_OK) == 0)
			return (ft_free_matrice(1, &paths), ft_free(1, &tmp), path);
		ft_free(2, &tmp, &path);
	}
	ft_free_matrice(1, &paths);
	return (NULL);
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*bin;

	if (!cmd || !env)
		return (NULL);
	paths = search_path_env(env);
	bin = find_bin(paths, cmd);
	return (bin);
}
