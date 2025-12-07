/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 02:30:15 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/07 02:43:57 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, int argc, char **argv)
{
	data->no_philo = ft_atoi(argv[1]);
	data->tt_die = ft_atol(argv[2]);
	data->tt_eat = ft_atol(argv[3]);
	data->tt_sleep = ft_atol(argv[4]);
	data->no_meals = -1;
	if (argc == 6)
		data->no_meals = ft_atoi(argv[5]);
}
