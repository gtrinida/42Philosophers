/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:40:05 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/26 02:28:44 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy(t_basic *basic)
{
	int	i;

	i = 0;
	while (i < basic->n_philo)
	{
		pthread_detach(basic->philo[i].thread_id);
		pthread_mutex_destroy(basic->philo->right_fork);
		pthread_mutex_destroy(basic->philo->left_fork);
		i++;
	}
	i = 0;
	while (i < basic->n_philo)
	{
		pthread_mutex_destroy(&basic->forks[i]);
		i++;
	}
	pthread_mutex_destroy(basic->print);
	free(basic->print);
	free(basic->philo);
	free(basic->forks);
	free(basic);
	return (0);
}

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
		destroy(basic);
		return (0);
	}
	while (1)
	{
		if (!spectator(basic))
			return (destroy(basic));
	}
}
