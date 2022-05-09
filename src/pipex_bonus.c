/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:42:45 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/05 23:19:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_get_doc(char *limiter, int *fd)
{
	char	*line;
	size_t	len;

	close(fd[0]);
	len = ft_strlen(limiter);
	while (1)
	{
		write(0, "pipex heredoc> ", 15);
		line = get_next_line(0);
		if (!line)
			break ;
		if (line[len] == '\n' && !ft_strncmp(line, limiter, len))
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
		ft_error("fork", 0);
	if (pid == 0)
	{
		close(fd[0]);
		ft_get_doc(limiter, fd);
	}
	else
	{
		close(fd[1]);
		wait(NULL);
	}
	return (fd[0]);
}

void	ft_child(char *cmd, char **env, int i, pid_t *tab)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	tab[i] = pid;
	if (!pid)
	{
		dup2(fd[1], STDOUT_FILENO);
		ft_exec(cmd, env);
		ft_close(fd[0], fd[1]);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		ft_close(fd[0], fd[1]);
	}
	// if (in != STDOUT_FILENO)
	// 	close(in);
}

void	ft_final(char *cmd, char **env, int out)
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
		dup2(fd[1], out);
		ft_exec(cmd, env);
		ft_close(fd[0], fd[1]);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		ft_close(fd[0], fd[1]);
	}
}

int	main(int ac, char **av, char **env)
{
	int	in;
	int	out;
	int	i;
	pid_t	tab[ac];

	if (ac < 5)
		exit(EXIT_FAILURE);
	i = 2;	
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
	{
		in = ft_here_doc(av[i++]);
		out = ft_open(av[ac - 1], 'A');
	}
	else
	{
		in = ft_open(av[1], 'R');
		out = ft_open(av[ac - 1], 'T');
	}
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	while (i < ac - 2)
	{
		ft_child(av[i], env, i, tab);
		i++;
	}
	ft_final(av[i], env, out);
	i = 2;
	while (i < ac - 1)
	{
		waitpid(tab[i], NULL, WNOHANG);
		i++;
	}
	wait(NULL);
	ft_close(in, out);
	return (0);
}


