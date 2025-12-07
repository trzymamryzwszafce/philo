/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 01:51:38 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/07 02:43:59 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data data;
	if (argc != 5 || argc != 6)
	{
		printf("Usage: n, t_t_die, t_t_eat, t_t_sleep, (n of meals)\n");
		return (1);
	}
	init_data(&data, argc, argv);
	return (0);
