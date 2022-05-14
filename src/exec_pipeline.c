/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:35:37 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/14 14:35:37 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec_first(t_data *data, char **env)
{
	data->childs[0] = fork();
	if (data->childs[0] < 0)
	{
		ft_free_data(data);
		return ;
	}
	if (!data->childs[0])
	{
		close(data->pipes[0][0]);
		dup2(data->in, STDIN_FILENO);
		dup2(data->pipes[0][1], STDOUT_FILENO);
		ft_close(data->in, data->pipes[0][1]);
		ft_exec(data->cmds[0], env, data);
		ft_free_data(data);
	}
	else
		ft_close(data->in, data->pipes[0][1]);
}

void	ft_exec_mid(t_data *data, char **env, ssize_t i)
{
	data->childs[i] = fork();
	if (data->childs[i] < 0)
	{
		ft_free_data(data);
		return ;
	}
	if (!data->childs[i])
	{
		close(data->pipes[i][0]);
		dup2(data->pipes[i - 1][0], STDIN_FILENO);
		dup2(data->pipes[i][1], STDOUT_FILENO);
		ft_close(data->pipes[i - 1][0], data->pipes[i][1]);
		ft_exec(data->cmds[i], env, data);
		ft_free_data(data);
	}
	else
		ft_close(data->pipes[i - 1][0], data->pipes[i][1]);
}

void	ft_exec_last(t_data *data, char **env)
{
	data->childs[data->nb_cmd - 1] = fork();
	if (data->childs[data->nb_cmd - 1] < 0)
	{
		ft_free_data(data);
		return ;
	}
	if (!data->childs[data->nb_cmd - 1])
	{
		close(data->pipes[data->nb_cmd - 2][1]);
		dup2(data->out, STDOUT_FILENO);
		dup2(data->pipes[data->nb_cmd - 2][0], STDIN_FILENO);
		ft_close(data->pipes[data->nb_cmd - 2][0], data->out);
		ft_exec(data->cmds[data->nb_cmd - 1], env, data);
		ft_free_data(data);
	}
	else
		ft_close(data->out, data->pipes[data->nb_cmd - 2][0]);
}

int	ft_wait_all(t_data *data)
{
	int		status;
	int		res;
	ssize_t	i;

	res = 0;
	i = -1;
	while (++i < data->nb_cmd)
	{
		waitpid(data->childs[i], &status, 0);
		if (WIFEXITED(status))
			res = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			res = WTERMSIG(status);
		else
			res = 1;
	}
	return (res);
}

void	ft_pipeline(t_data *data, char **env)
{
	ssize_t	i;

	i = 0;
	ft_exec_first(data, env);
	while (++i < data->nb_cmd - 1)
		ft_exec_mid(data, env, i);
	ft_exec_last(data, env);
	ft_wait_all(data);
}
