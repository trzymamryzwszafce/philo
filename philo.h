/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 01:42:42 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/12 18:51:47 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					id;
	int					l_fork;
	int					r_fork;
	int					eat_num;
	long				last_meal;
	struct s_data		*data;
}		t_philo;

typedef struct s_data
{
	int					no_philo;
	long				tt_die;
	long				tt_eat;
	long				tt_sleep;
	int					no_meals;
	long				start_time;
	bool				philo_ded;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		death_lock;
	pthread_mutex_t		meal_lock;
	t_philo				*philos;
}		t_data;

int		init_data(t_data *data, int argc, char **argv);
int		init_forks(t_data *data);
int		init_philos(t_data *data);
int		init_threads(t_data *data);
void	join_threads(t_data *data, pthread_t *threads);
int		handle_one_philo(t_data *data);
int		create_threads(t_data *data, pthread_t *threads);
void	*monitor(void *arg);
void	*routine(void *arg);

void	get_fork_order(t_philo *philo);
void	unlock_forks(t_philo *philo);
int		check_death(t_philo *philo);
long	get_time(void);
void	cleanup(t_data *data);
long	ft_atol(const char *str);
int		ft_atoi(const char *str);
void	ft_usleep(t_data *data, unsigned long long time_to_sleep);

#endif
