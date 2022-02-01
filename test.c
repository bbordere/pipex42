/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:42:45 by bbordere          #+#    #+#             */
/*   Updated: 2022/02/01 15:59:27 by bbordere         ###   ########.fr       */
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

int main(int argc, char *argv[], char **env)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
	{
		printf("ERROR !");
		exit (1);
	}
	pid = fork();
	if (!argv[1])
		return 1;
	ft_exec(argv[1], env);
	return 0;
}



/*
void main(void)
{
	int fd[2];
	int child;
	char buff[1024];

	if (pipe(fd) == -1)
	{
		printf("ERROR !");
		exit (10);
	}
	child = fork();
	if (child == -1)
		printf("ERROR FORK");
	else if (child)
	{
		printf("CHILD PROC");
		close(fd[1]);
		if (read(fd[0], buff, 1024) < 0)
			printf("ERROR READING");
		printf(" >> %s\n", buff);
		close(fd[0]);
	}
	else
	{
		printf("PARENT PROC\n");
		close(fd[0]);
		if (write(fd[1], DATA, sizeof(DATA)) < 0)
			printf("ERROR WRITING");
		close(fd[1]);
	}

}*/
