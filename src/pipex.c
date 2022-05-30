/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:42:45 by bbordere          #+#    #+#             */
/*   Updated: 2022/04/23 18:22:13 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	int		ret;

	if (ac != 5)
		return (write(1, "Wrong number of arguments !\n", 29), 1);
	data = ft_init_data(ac, av);
	if (!data)
		exit(EXIT_FAILURE);
	ft_exec_first(data, env);
	ft_exec_last(data, env);
	ret = ft_wait_all(data);
	ft_free_data(data);
	return (ret);
}
