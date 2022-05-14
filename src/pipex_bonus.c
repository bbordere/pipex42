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

	if (ac < 5)
		exit(EXIT_FAILURE);
	data = ft_init_data(ac, av);
	ft_pipeline(data, env);
	ft_free_data(data);
	return (0);
}
