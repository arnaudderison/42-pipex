/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnaud <arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:44:53 by arnaud            #+#    #+#             */
/*   Updated: 2024/01/07 16:35:56 by arnaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "libft.h"

# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHITW "\x1B[37m"
# define RESET "\x1B[0m"

# define NB_ARGS_ERR "Number(s) of args is invalide\n"
# define NO_ENV_ERR "Undetected environment variable\n"

typedef struct s_pipex
{
	char	**cmds;
	char	***s_cmds;
	int		cmdc;
	int		fd_input;
	int		fd_output;
}			t_pipex;

#endif
