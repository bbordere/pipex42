/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:42:45 by bbordere          #+#    #+#             */
/*   Updated: 2022/02/02 22:09:11 by bbordere         ###   ########.fr       */
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
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "libft/libft.h"

char	*ft_path(char *cmd, char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (!ft_strnstr(env[i], "PATH", 4))
		i++;
	path = ft_split(env[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(ft_strjoin(path[i], "/"), cmd);
		if (access(path[i], F_OK) == 0)
			return (path[i]);
		i++;
	}
	return (NULL);
}

void	ft_exec(char *str, char **env)
{
	char	*path;
	char	**args;

	args = ft_split(str, ' ');
	path = ft_path(args[0], env);
	if (execve(path, args, env) == -1)
		return ;
}

void	ft_parent(int *fd, char **av, char **env)
{
	int	out;

	out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(out, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	ft_exec(av[3], env);
}

void	ft_child(int *fd, char **av, char **env)
{
	int	in;

	in = open(av[1], O_RDONLY);
	dup2(in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	ft_exec(av[2], env);
}

int main(int argc, char *argv[], char **env)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
	{
		printf("ERROR !");
		exit (1);
	}
	pid1 = fork();
	if (pid1 == -1)
		return 2;
		
	if (pid1 == 0)
		ft_child(fd, argv, env);
	else
		ft_parent(fd, argv, env);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	return 0;
}
