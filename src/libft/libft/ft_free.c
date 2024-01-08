/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnaud <arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:05:37 by arnaud            #+#    #+#             */
/*   Updated: 2024/01/08 21:08:27 by arnaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(unsigned int count, ...)
{
	va_list	args;
	void	**tmp;

	va_start(args, count);
	while (count--)
	{
		tmp = va_arg(args, void **);
		if (*tmp)
		{
			free(*tmp);
			*tmp = NULL;
		}
	}
	va_end(args);
}
