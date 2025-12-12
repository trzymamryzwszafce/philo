/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:48:13 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/12 18:51:15 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_one_philo(t_data *data)
{
	printf("%ld 1 has taken a fork\n", 0L);
	usleep(data->tt_die * 1000);
	printf("%ld 1 died\n", data->tt_die);
	return (0);
}

int	create_threads(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->no_philo)
	{
		if (pthread_create(&threads[i], NULL, routine, &data->philos[i]))
			return (1);
		i++;
	}
	return (0);
}

void	join_threads(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->no_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
