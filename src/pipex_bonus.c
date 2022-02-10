/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:42:45 by bbordere          #+#    #+#             */
/*   Updated: 2022/02/10 17:01:05 by bbordere         ###   ########.fr       */
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

void	ft_here_doc(char *limiter)
{
	int		fd[2];
	int		pid;
	char	*line;

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		ft_error();
	if (pid == 0)
	{
		close(fd[0]);
		line = get_next_line(0);
		while (line)
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
			line = get_next_line(0);
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	ft_child(char *cmd, char **env)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		ft_error();
	if (!pid)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_exec(cmd, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int	main(int ac, char **av, char **env)
{
	int	in;
	int	out;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			out = ft_open(av[ac - 1], 2);
			ft_here_doc(av[2]);
			av++;
		}
		else
		{
			if (access(av[1], F_OK) != 0)
				ft_error();
			in = ft_open(av[1], 0);
			out = ft_open(av[ac - 1], 1);
			dup2(in, STDIN_FILENO);
		}
		av++;
		while (*(++av + 2))
			ft_child(*av, env);
		dup2(out, STDOUT_FILENO);
		ft_exec(*av, env);
	}
}
