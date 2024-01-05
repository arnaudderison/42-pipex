/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnaud <arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:05:22 by arnaud            #+#    #+#             */
/*   Updated: 2024/01/05 22:17:10 by arnaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (argc != 5 || !argv)
		return (ft_putstr_fd(RED NB_ARGS_ERR RESET, 2));
	if (!env)
		return (ft_putstr_fd(RED NO_ENV_ERR RESET, 2));
	return (1);
}
