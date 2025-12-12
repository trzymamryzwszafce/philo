/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:02:50 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/12 18:17:53 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_status(t_philo *philo, char *str)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->philo_ded)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return (0);
	}
	pthread_mutex_lock(&philo->data->print_lock);
	timestamp = get_time() - philo->data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_lock);
	pthread_mutex_unlock(&philo->data->death_lock);
	return (1);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data, philo->data->tt_sleep * 1000);
}

void	philo_eat(t_philo *philo)
{
	get_fork_order(philo);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->meal_lock);
	if (!print_status(philo, "has taken a fork"))
		return (unlock_forks(philo));
	if (!print_status(philo, "is eating"))
		return (unlock_forks(philo));
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->eat_num++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_usleep(philo->data, philo->data->tt_eat * 1000);
	unlock_forks(philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data, 500);
	while (!check_death(philo))
	{
		philo_eat(philo);
		if (check_death(philo))
			break ;
		philo_sleep(philo);
		if (check_death(philo))
			break ;
		philo_think(philo);
	}
	return (NULL);
}
