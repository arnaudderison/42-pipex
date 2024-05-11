/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_exist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:27:56 by aderison          #+#    #+#             */
/*   Updated: 2024/05/10 11:33:47 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**path_exist(char **env)
{
	if (!*env)
		return (NULL);
	while (!ft_strnstr(*env, "PATH", 4))
	{
		if (*env == NULL)
			return (NULL);
		env++;
	}
	return (ft_split(*env + 5, ':'));
}
