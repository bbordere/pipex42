/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:42:45 by bbordere          #+#    #+#             */
/*   Updated: 2022/02/14 16:49:48 by bbordere         ###   ########.fr       */
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

void	ft_get_doc(char *limiter, int *fd)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("pipex heredoc> ", 1);
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			close(fd[1]);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
}

void	ft_here_doc(char *limiter)
{
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		ft_error("fork");
	if (pid == 0)
	{
		close(fd[0]);
		ft_get_doc(limiter, fd);
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
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
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

void	ft_check_open(char *filename)
{
	int	in;

	if (access(filename, F_OK) != 0)
		ft_error(filename);
	in = ft_open(filename, 0);
	if (in == -1)
		ft_error(filename);
	dup2(in, STDIN_FILENO);
	close(in);
}

int	main(int ac, char **av, char **env)
{
	int	out;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			ft_here_doc(av[2]);
			out = ft_open(av[ac - 1], 2);
			av += 2;
		}
		else
		{
			ft_check_open(av[1]);
			out = ft_open(av[ac - 1], 1);
			av++;
		}
		while (*(++av + 2))
			ft_child(*av, env);
		dup2(out, STDOUT_FILENO);
		ft_exec(*av, env);
	}
}
