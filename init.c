/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 02:30:15 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/11 03:32:28 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_data *data)
{
	int			i;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * data->no_philo);
	if (!threads)
		return (1);
	i = 0;
	while (i < data->no_philo)
	{
		if (pthread_create(&threads[i], NULL, routine, &data->philos[i]))
		{
			free(threads);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < data->no_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->no_philo);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->no_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_num = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].l_fork = i;
		data->philos[i].r_fork = (i + 1) % data->no_philo;
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->no_philo);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->no_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->death_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->meal_lock, NULL))
		return (1);
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->no_philo = ft_atoi(argv[1]);
	if (!argv[1] || data->no_philo <= 0)
		return (1);
	data->tt_die = ft_atoi(argv[2]);
	if (!argv[2] || data->tt_die <= 0)
		return (1);
	data->tt_eat = ft_atoi(argv[3]);
	if (!argv[3] || data->tt_eat <= 0)
		return (1);
	data->tt_sleep = ft_atoi(argv[4]);
	if (!argv[4] || data->tt_sleep <= 0)
		return (1);
	data->philo_ded = false;
	data->no_meals = 0;
	if (argc == 6)
	{
		data->no_meals = ft_atoi(argv[5]);
		if (!argv[5] || data->no_meals < 0)
			return (1);
	}
	gettimeofday(&data->start_time, NULL);
	return (0);
}
