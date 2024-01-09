/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleantab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnaud <arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:13:52 by arnaud            #+#    #+#             */
/*   Updated: 2024/01/09 00:09:39 by arnaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static void	free_tab_of_tabs(char ***tab)
{
	int	i;
	int	j;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			free(tab[i][j]);
			j++;
		}
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	***cleantab(char **tab, int size)
{
	char	***ret;
	int		i;

	ret = (char ***)malloc(sizeof(char **) * (size + 1));
	if (!ret || !tab)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		ret[i] = ft_split(tab[i + 2], ' ');
		if (!ret[i])
			free_tab_of_tabs(&ret[i]);
	}
	ret[size] = NULL;
	return (ret);
}
