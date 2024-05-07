/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:02:28 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/02/19 17:38:59 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_str(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	fd_close(t_pipex *pipex, int a)
{
	close(pipex->infile);
	close(pipex->outfile);
	if (a == 0)
	{
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		perror("cmd_and_parh");
	}
	else if (a == 2)
	{
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		perror("Fork:");
	}
	else if (a == 1)
	{
		close(pipex->pipefd[0]);
		perror("Fork:");
	}
	else
	{
		close(pipex->pipefd[0]);
	}
}

static char	*path_env(char **env)
{
	char	*sub;

	while (*env && ft_strncmp(*env, "PATH=", 5))
		env++;
	sub = ft_substr(*env, 5, ft_strlen(*env) - 5);
	if (!sub)
		return (NULL);
	return (sub);
}

static char	*cmd_and_path(char *cmd, char **path)
{
	char	*sub;
	char	*cmd_and_path;
	int		i;

	sub = ft_strjoin("/", cmd);
	if (!sub)
		return (NULL);
	i = 0;
	while (path[i])
	{
		cmd_and_path = ft_strjoin(path[i], sub);
		if (access(cmd_and_path, F_OK) == 0)
			return (free(sub), cmd_and_path);
		free(cmd_and_path);
		i++;
	}
	return (free(sub), NULL);
}

char	*find_path(t_pipex pipex, char *cmd, char **env)
{
	char	**path;
	char	*sub;
	char	**cmd1;

	cmd1 = ft_split(cmd, ' ');
	if (!cmd1)
		return (NULL);
	sub = path_env(env);
	if (!sub)
		return (free(cmd1), NULL);
	path = ft_split(sub, ':');
	if (!path)
		return (free(sub), free_str(cmd1), NULL);
	free(sub);
	pipex.cmd_and_path = cmd_and_path(*cmd1, path);
	free_str(path);
	free_str(cmd1);
	if (!pipex.cmd_and_path)
	{
		ft_putstr_fd("Access: There is no way\n", 2);
		return (NULL);
	}
	return (pipex.cmd_and_path);
}
