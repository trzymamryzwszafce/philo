/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 01:50:14 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/12 18:12:01 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_death(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->death_lock);
	philo->data->philo_ded = true;
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_lock(&philo->data->print_lock);
	timestamp = get_time() - philo->data->start_time;
	printf("%ld %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->data->print_lock);
}

int	check_all_ate(t_data *data)
{
	int	i;

	if (data->no_meals == 0)
		return (0);
	i = 0;
	pthread_mutex_lock(&data->meal_lock);
	while (i < data->no_philo)
	{
		if (data->philos[i].eat_num < data->no_meals)
		{
			pthread_mutex_unlock(&data->meal_lock);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&data->meal_lock);
	return (1);
}

int	check_death_condition(t_data *data)
{
	int		i;
	long	time;

	i = 0;
	while (i < data->no_philo)
	{
		pthread_mutex_lock(&data->meal_lock);
		time = get_time();
		if (time - data->philos[i].last_meal > data->tt_die + 5)
		{
			pthread_mutex_unlock(&data->meal_lock);
			print_death(&data->philos[i]);
			return (1);
		}
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_all_ate(data))
		{
			pthread_mutex_lock(&data->death_lock);
			data->philo_ded = true;
			pthread_mutex_unlock(&data->death_lock);
			return (NULL);
		}
		if (check_death_condition(data))
			return (NULL);
		ft_usleep(data, 100);
	}
	return (NULL);
}
