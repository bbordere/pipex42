/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:50:47 by bbordere          #+#    #+#             */
/*   Updated: 2022/04/23 18:42:32 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open(char *filename, char mode)
{
	int	file;

	if (mode == 'R')
	{
		if (access(filename, F_OK) == 0)
			file = open(filename, O_RDONLY);
		else
		{
			perror(filename);
			exit(EXIT_FAILURE);
		}
	}
	else if (mode == 'T')
		file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (mode == 'A')
		file = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0664);
	return (file);
}

void	ft_error(char *str, int mode)
{
	if (mode)
	{	
		write(2, "pipex: ", 7);
		write(2, str, ft_strlen(str));
		write(2, ": command not found\n", 20);
		if (mode > 2)
			close(mode);
		else
			exit(127);
	}
	else
	{
		perror(str);
		exit(EXIT_FAILURE);
	}
}

void	*ft_free(char **tab)
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
	return (NULL);
}

char	*ft_path(char *cmd, char **env)
{
	char	**path;
	int		i;

	i = open(cmd, __O_DIRECTORY);
	if (i > 0)
		ft_error(cmd, i);
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	if (!env || !*env)
		return (NULL);
	i = 0;
	while (!ft_strnstr(env[i], "PATH", 4))
		i++;
	path = ft_split(env[i] + 5, ':');
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		path[i] = ft_strjoin(ft_strjoin(path[i], "/"), cmd);
		if (path[i] && access(path[i], X_OK) == 0)
			return (path[i]);
	}
	return (ft_free(path));
}

void	ft_exec(char *str, char **env)
{
	char	*path;
	char	**args;

	args = ft_split(str, ' ');
	if (!args)
		ft_error("split", 0);
	path = ft_path(args[0], env);
	if (!path)
	{
		write(2, "pipex: ", 7);
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": command not found\n", 20);
		ft_free(args);
		exit(127);
	}
	else if (execve(path, args, env) == -1)
	{
		ft_free(args);
		exit(127);
	}
}
