/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:42:45 by bbordere          #+#    #+#             */
/*   Updated: 2022/02/14 22:12:02 by bbordere         ###   ########.fr       */
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

int	ft_here_doc(char *limiter)
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
		waitpid(pid, NULL, 0);		
	}
	return (fd[0]);
}

void	ft_child(char *cmd, char **env, int in)
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
		if (in == STDIN_FILENO)
			exit(EXIT_FAILURE);
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

	
	in = ft_open(filename, 'R');
	if (in == -1)
		ft_error(filename);
	dup2(in, STDIN_FILENO);
	close(in);
}

int	main(int ac, char **av, char **env)
{
	int	in;
	int	out;
	int	i;

	if (ac >= 5)
	{
		i = 2;
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			in = ft_here_doc(av[2]);
			out = ft_open(av[ac - 1], 'A');
			i++;
		}
		else
		{
			in = ft_open(av[1], 'R');
			out = ft_open(av[ac - 1], 'T');
		}		
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		ft_child(av[i], env, in);
		while (++i < ac - 2)
			ft_child(av[i], env, STDOUT_FILENO);
		ft_exec(av[i], env);
	}
	return (1);
}
