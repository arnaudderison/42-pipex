/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:06:55 by aderison          #+#    #+#             */
/*   Updated: 2024/05/11 01:29:12 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define RESET "\x1B[0m"

typedef struct s_pipex
{
	char	**path;
	char	***cmds;
	int		cmdc;
	int		fd_input;
	int		fd_output;
}			t_pipex;

# define NB_ARGS_ERR "Number(s) of args is invalide\n"
# define ENV_ERR \
	"Invalid ENV\n [+] Check if the PATH environment variable is \
available by typing env in your terminal"
# define ERR_POINTER_NULL "POINTER NULL ERROR : \n"

char		**path_exist(char **env);
int			init_struct(t_pipex *pipex, char *input, char *output, char **cmds,
				int argc);
void		exit_pipex(t_pipex *pipex, char *msg, int error);

#endif