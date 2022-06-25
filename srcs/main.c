/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:40:05 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/25 20:05:08 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	spectator(t_basic *basic)
{
	int	i;
	int	time;

	i = -1;
	while (++i < basic->n_philo)
	{
		time = get_time()
			- basic->philo[i].start_time
			- basic->philo[i].ate_last_time;
		if (time > basic->time_to_die)
		{
			pthread_mutex_lock(basic->philo[i].print);
			usleep(500);
			if (basic->philo[i].eat_counter > 0
				|| basic->philo[i].eat_counter == -1)
				printf("%d %d died\n", get_time()
					- basic->philo[i].start_time, i + 1);
			return (0);
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_basic	*basic;

	basic = malloc(sizeof(t_basic));
	if (!basic)
		return (1);
	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of arguments\n");
		return (0);
	}
	if (!basic_init(argc, argv, basic))
		return (1);
	philo_init(basic);
	if (threads_init(basic) != 0)
	{
		destroy_threads(basic);
		return (0);
	}
	while (1)
	{
		if (!spectator(basic))
			return (destroy_threads(basic));
	}
}