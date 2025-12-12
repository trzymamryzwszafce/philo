/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 02:34:52 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/12 18:18:15 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	val;
	int	i;

	res = 0;
	val = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			val = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (val * res);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	cleanup(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->no_philo)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->meal_lock);
	if (data->philos)
		free(data->philos);
	free(data);
}

void	ft_usleep(t_data *data, unsigned long long time_to_sleep)
{
	unsigned long long	start;
	unsigned long long	current;

	start = get_time() * 1000;
	while (1)
	{
		pthread_mutex_lock(&data->death_lock);
		if (data->philo_ded)
		{
			pthread_mutex_unlock(&data->death_lock);
			return ;
		}
		pthread_mutex_unlock(&data->death_lock);
		current = get_time() * 1000;
		if (current - start >= time_to_sleep)
			break ;
		usleep(100);
	}
}
