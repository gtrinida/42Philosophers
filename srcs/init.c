/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:40:11 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/25 22:12:47 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parser(int argc, char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0)
		return (0);
	if (ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
		return (0);
	if (argc > 5 && ft_atoi(argv[5]) < 0)
		return (0);
	return (1);
}

void	philo_init(t_basic *basic)
{
	int	i;

	i = -1;
	pthread_mutex_init(basic->print, NULL);
	while (++i < basic->n_philo)
		pthread_mutex_init(&basic->forks[i], NULL);
	i = -1;
	while (++i < basic->n_philo)
	{
		basic->philo[i].index = i + 1;
		basic->philo[i].time_to_eat = basic->time_to_eat;
		basic->philo[i].time_to_sleep = basic->time_to_sleep;
		basic->philo[i].ate_last_time = 0;
		basic->philo[i].start_time = basic->start_time;
		basic->philo[i].print = basic->print;
		basic->philo[i].eat_counter = basic->eat_count;
		basic->philo[i].left_fork = &basic->forks[i];
		basic->philo[i].right_fork
			= &basic->forks[(i + 1) % basic->n_philo];
	}
}

int	basic_init_utils(t_basic *basic, int argc, char **argv)
{
	basic->n_philo = ft_atoi(argv[1]);
	if (!basic->n_philo)
	{
		free(basic);
		return (0);
	}
	basic->time_to_die = ft_atoi(argv[2]);
	basic->time_to_eat = ft_atoi(argv[3]);
	basic->time_to_sleep = ft_atoi(argv[4]);
	if (argc < 6)
		basic->eat_count = -1;
	else
		basic->eat_count = ft_atoi(argv[5]);
	return (1);
}

int	basic_init(int argc, char **argv, t_basic *basic)
{
	if (!parser(argc, argv))
	{
		free(basic);
		printf("Arguments isn't valid\n");
		return (0);
	}
	if (!basic_init_utils(basic, argc, argv))
		return (0);
	basic->philo = malloc(sizeof(t_philo) * basic->n_philo);
	basic->forks = malloc(sizeof(t_mutex) * basic->n_philo);
	basic->print = malloc(sizeof(t_mutex));
	if (!basic->forks || !basic->philo || !basic->print)
		return (0);
	basic->start_time = get_time();
	return (1);
}
