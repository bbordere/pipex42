/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:50:47 by bbordere          #+#    #+#             */
/*   Updated: 2022/04/06 00:16:15 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open(char *filename, char mode, int infile)
{
	int	file;

	if (mode == 'R')
	{
		if (access(filename, F_OK) == 0)
			file = open(filename, O_RDONLY);
		else
		{
			perror(filename);
			if (infile == 1)
				return (STDIN_FILENO);
			else
				exit(EXIT_FAILURE);
		}
	}
	else if (mode == 'T')
		file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (mode == 'A')
		file = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0664);
	return (file);
}

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	ft_free(char **tab)
{
	int	i;

	if (tab)
	{
		i = -1;
		while (tab[++i])
			if (tab[i])
				free(tab[i]);
		free(tab);
		tab = NULL;
	}
}

char	*ft_path(char *cmd, char **env)
{
	char	**path;
	int		i;

	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	i = 0;
	while (!ft_strnstr(env[i], "PATH", 4))
		i++;
	path = ft_split(env[i] + 5, ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(ft_strjoin(path[i], "/"), cmd);
		if (path[i] && access(path[i], X_OK) == 0)
			return (path[i]);
		i++;
	}
	ft_free(path);
	return (NULL);
}

void	ft_exec(char *str, char **env)
{
	char	*path;
	char	**args;

	args = ft_split(str, ' ');
	if (!args)
		ft_error("split");
	path = ft_path(args[0], env);
	if (!path)
	{
		perror(args[0]);
		ft_free(args);
		exit(EXIT_FAILURE);
	}
	else if (execve(path, args, env) == -1)
	{
		ft_free(args);
		exit(127);
	}
}
