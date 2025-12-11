/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 01:51:38 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/11 03:32:28 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		*data;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: n, t_t_die, t_t_eat, t_t_sleep, (n of meals)\n");
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (init_data(data, argc, argv))
		return (free(data), 1);
	if (init_forks(data))
		return (free(data), 1);
	if (init_philos(data))
		return (cleanup(data), 1);
	if (init_threads(data))
		return (cleanup(data), 1);
	cleanup(data);
	return (0);
}
