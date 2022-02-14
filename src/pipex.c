/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:42:45 by bbordere          #+#    #+#             */
/*   Updated: 2022/02/14 23:37:05 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// < file1 cmd1 | cmd2 > file2 :
// read content of  files1
// send it to cmd1
// send cmd1's output to cmd2
// write cmd2's output in file2

// file1 = av[1], cmd1 = av[2], cmd2 = av[3], file2 = av[4]
// fd[2] : fd[0] = input (reading) fd[1] = output (writing)
// child read ||  parent write

// pipe(fd) == -1 : return ERROR;
#include "pipex.h"

void	ft_parent(int *fd, char **av, char **env)
{
	int	out;

	out = ft_open(av[4], 'T', 0);
	if (out == -1)
		ft_error("open failed");
	dup2(out, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	ft_exec(av[3], env);
}

void	ft_child(int *fd, char **av, char **env)
{
	int	in;

	if (access(av[1], F_OK) != 0)
		ft_error(av[1]);
	in = ft_open(av[1], 'R', 0);
	if (in == -1)
		ft_error(av[1]);
	dup2(in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	ft_exec(av[2], env);
}

int	main(int ac, char **av, char **env)
{
	int	fd[2];
	int	pid;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			ft_error("pipe failed");
		pid = fork();
		if (pid == -1)
			ft_error("fork");
		if (!pid)
			ft_child(fd, av, env);
		else
			ft_parent(fd, av, env);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, NULL, 0);
	}
}
