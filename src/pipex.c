/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:42:45 by bbordere          #+#    #+#             */
/*   Updated: 2022/04/23 18:22:13 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parent(int *fd, char **av, char **env)
{
	int	out;

	out = ft_open(av[4], 'T');
	if (out == -1)
		ft_error("open failed", 0);
	dup2(out, STDOUT_FILENO);
	close(out);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	ft_exec(av[3], env);
	wait(NULL);
}

void	ft_child(int *fd, char **av, char **env)
{
	int	in;

	if (access(av[1], F_OK) != 0)
		ft_error(av[1], 0);
	in = ft_open(av[1], 'R');
	if (in == -1)
		ft_error(av[1], 0);
	dup2(in, STDIN_FILENO);
	close(in);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	ft_exec(av[2], env);
}

int	main(int ac, char **av, char **env)
{
	int	fd[2];
	int	pid;

	if (ac != 5)
		return (printf("Wrong number of arguments !\n"), 1);
	if (pipe(fd) == -1)
		ft_error("pipe failed", 0);
	pid = fork();
	if (pid == -1)
		ft_error("fork", 0);
	if (!pid)
		ft_child(fd, av, env);
	else
		ft_parent(fd, av, env);
	ft_close(fd[0], fd[1]);
	waitpid(pid, NULL, 0);
}
