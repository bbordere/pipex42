/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 10:34:00 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/14 10:34:00 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	int		ret;

	if (ac < 5)
		return (printf("Wrong number of arguments !\n"), 1);
	data = ft_init_data(ac, av);
	ret = ft_pipeline(data, env);
	ft_free_data(data);
	return (ret);
}
