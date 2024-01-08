/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrice.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnaud <arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:08:04 by arnaud            #+#    #+#             */
/*   Updated: 2024/01/08 21:09:56 by arnaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_matrice(unsigned int count, ...)
{
	va_list	args;
	void	***tab;
	int		i;

	va_start(args, count);
	while (count--)
	{
		tab = va_arg(args, void ***);
		if (*tab)
		{
			i = 0;
			while ((*tab)[i])
			{
				free((*tab)[i]);
				(*tab)[i++] = NULL;
			}
			free(*tab);
			*tab = NULL;
		}
	}
	va_end(args);
}
