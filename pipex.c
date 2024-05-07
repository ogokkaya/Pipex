/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:02:34 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/02/19 17:41:00 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

void	second_child(t_pipex pipex, char **av, char **env)
{
	int		execvevalue;
	char	**cmd;

	cmd = ft_split(av[3], ' ');
	execvevalue = 0;
	close(pipex.pipefd[1]);
	dup2(pipex.outfile, 1);
	dup2(pipex.pipefd[0], 0);
	execvevalue = execve(pipex.cmd_and_path, cmd, env);
	if (execvevalue == -1)
	{
		free_str(cmd);
		perror("Second child execve");
		exit(1);
	}
	free_str(cmd);
	exit(0);
}

void	first_child(t_pipex pipex, char **av, char **env)
{
	int		execvevalue;
	char	**cmd;

	cmd = ft_split(av[2], ' ');
	execvevalue = 0;
	close(pipex.pipefd[0]);
	dup2(pipex.infile, 0);
	dup2(pipex.pipefd[1], 1);
	execvevalue = execve(pipex.cmd_and_path, cmd, env);
	if (execvevalue == -1)
	{
		free_str(cmd);
		perror("First child execve");
		exit(1);
	}
	free_str(cmd);
	exit(0);
}

int	check(t_pipex *pipex, int ac, char **av)
{
	if (ac != 5)
	{
		ft_putstr_fd("Format!\n", 2);
		ft_putstr_fd("./pipex <infile> <cmd=1> <cmd=2> <outfile>\n", 2);
		return (0);
	}
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile == -1)
		return (perror("infile"), 0);
	pipex->outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (pipex->outfile == -1)
		return (perror("outfile"), 0);
	pipex->pipevalue = pipe(pipex->pipefd);
	if (pipex->pipevalue == -1)
		return (perror("pipe"), 0);
	if (av[2][0] == '\0')
		return (perror("Cmd=1"), 0);
	if (av[3][0] == '\0')
		return (perror("Cmd=2"), 0);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (check(&pipex, ac, av) == 0)
		return (0);
	pipex.cmd_and_path = find_path(pipex, av[2], env);
	if (!pipex.cmd_and_path)
		return (fd_close(&pipex, 0), 0);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		return (free(pipex.cmd_and_path), fd_close(&pipex, 2), 0);
	else if (pipex.pid1 == 0)
		first_child(pipex, av, env);
	waitpid(-1, NULL, 0);
	close(pipex.pipefd[1]);
	free(pipex.cmd_and_path);
	pipex.cmd_and_path = find_path(pipex, av[3], env);
	if (!pipex.cmd_and_path)
		return (fd_close(&pipex, 1), 0);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		return (free(pipex.cmd_and_path), fd_close(&pipex, 1), 0);
	else if (pipex.pid2 == 0)
		second_child(pipex, av, env);
	waitpid(-1, NULL, 0);
	return (free(pipex.cmd_and_path), fd_close(&pipex, 3), 0);
}
