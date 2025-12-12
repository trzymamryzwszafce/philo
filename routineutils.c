/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routineutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 02:58:04 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/12 17:55:31 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
}

void	get_fork_order(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
	}
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->philo_ded)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	return (0);
}
