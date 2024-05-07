/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:02:36 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/02/19 17:23:17 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	*cmd_and_path;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		pipevalue;
	int		infile;
	int		outfile;
}			t_pipex;

char		*find_path(t_pipex pipex, char *cmd, char **env);
void		fd_close(t_pipex *pipex, int a);
void		free_str(char **str);
#endif
