/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:50:47 by bbordere          #+#    #+#             */
/*   Updated: 2022/02/10 15:57:34 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		ft_open(char *filename, int mode)
{
	int	file;

	if (mode == 0)
		file = open(filename, O_RDONLY);
	else if (mode == 1)
		file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == 2)
		file = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file == -1)
		return (-1);
	return (file);
}

void	ft_error(void)
{
	perror("pipex");
	exit(EXIT_FAILURE);
}

void	ft_free(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char	*ft_path(char *cmd, char **env)
{
	char	**path;
	int		i;

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
		if (path[i] && access(path[i], F_OK) == 0)
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
		ft_error();
	path = ft_path(args[0], env);
	if (!path || execve(path, args, env) == -1)
	{
		ft_free(args);
		ft_error();
	}
}
