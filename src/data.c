/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:37:10 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/14 14:37:10 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init_files(t_data *data, int ac, char **av)
{
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
	{
		data->here_doc = 1;
		data->nb_cmd--;
		data->in = ft_here_doc(av[2]);
		data->out = ft_open(av[ac - 1], 'A');
	}
	else
	{
		data->here_doc = 0;
		data->in = ft_open(av[1], 'R');
		data->out = ft_open(av[ac - 1], 'T');
	}
	if (data->in == -1)
	{
		ft_free_data(data);
		write(2, "pipex: ", 8);
		write(2, av[1], ft_strlen(av[1]));
		write(2, ": No such file or directory\n", 28);
		exit(EXIT_SUCCESS);
	}
}

int	**ft_init_pipes(t_data *data)
{
	ssize_t	i;
	int		**pipes;

	i = -1;
	pipes = malloc(sizeof(int *) * data->nb_cmd - 1);
	if (!pipes)
		return (NULL);
	while (++i < (data->nb_cmd - 1))
		pipes[i] = NULL;
	i = -1;
	while (++i < (data->nb_cmd - 1))
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (NULL);
		pipe(pipes[i]);
	}
	return (pipes);
}

char	**ft_init_cmds(t_data *data, char **av)
{
	char	**cmds;
	ssize_t	i;

	cmds = malloc(sizeof(char *) * (data->nb_cmd + 1));
	if (!cmds)
		return (NULL);
	i = -1;
	while (++i < data->nb_cmd)
	{
		cmds[i] = ft_strdup(av[i + 2 + data->here_doc]);
		if (!cmds[i])
			return (NULL);
	}
	cmds[i] = NULL;
	return (cmds);
}

t_data	*ft_init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->nb_cmd = ac - 3;
	data->cmds = NULL;
	data->in = -1;
	data->out = -1;
	data->childs = malloc(sizeof(pid_t) * data->nb_cmd);
	if (!data->childs)
		return (free(data), NULL);
	data->pipes = ft_init_pipes(data);
	if (!data->pipes)
		return (ft_free_data(data), NULL);
	ft_init_files(data, ac, av);
	if (data->out == -1)
	{
		ft_free_data(data);
		ft_error("open failed", 0);
	}
	data->cmds = ft_init_cmds(data, av);
	if (!data->cmds)
		return (ft_free_data(data), NULL);
	return (data);
}

void	ft_free_data(t_data *data)
{
	ssize_t	i;

	i = -1;
	if (data->pipes)
	{
		while (++i < data->nb_cmd - 1)
		{
			ft_close(data->pipes[i][0], data->pipes[i][1]);
			free(data->pipes[i]);
		}
		free(data->pipes);
	}
	free(data->childs);
	if (data->cmds)
		ft_free(data->cmds);
	if (data->in != -1)
		close(data->in);
	if (data->out != -1)
		close(data->out);
	free(data);
}
