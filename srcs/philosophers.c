/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:40:29 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/25 20:05:29 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(philo->left_fork);
	time = get_time() - philo->start_time;
	pthread_mutex_lock(philo->print);
	printf("%d %d has taken a fork\n", time, philo->index);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->right_fork);
	time = get_time() - philo->start_time;
	pthread_mutex_lock(philo->print);
	printf("%d %d has taken a fork\n",
		time, philo->index);
	pthread_mutex_unlock(philo->print);
}

void	eating(t_philo *philo)
{
	philo->ate_last_time = get_time() - philo->start_time;
	pthread_mutex_lock(philo->print);
	printf("%d %d is eating\n", philo->ate_last_time,
		philo->index);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	int	time;

	time = get_time() - philo->start_time;
	pthread_mutex_lock(philo->print);
	printf("%d %d is sleeping\n", time, philo->index);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->time_to_sleep);
	time = get_time() - philo->start_time;
	pthread_mutex_lock(philo->print);
	printf("%d %d is thinking\n", time, philo->index);
	pthread_mutex_unlock(philo->print);
}

void	*philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_detach(philo->thread_id);
	while (philo->eat_counter != 0)
	{
		take_forks(philo);
		eating(philo);
		sleeping(philo);
		if (philo->eat_counter > 0)
			philo->eat_counter--;
		if (!philo->eat_counter)
			return (0);
	}
	return (0);
}

int	threads_init(t_basic *basic)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < basic->n_philo)
	{
		if (i % 2 == 0)
		{
			status |= pthread_create(&basic->philo[i].thread_id,
					NULL, &philo, &basic->philo[i]);
			usleep(200);
		}
	}
	i = -1;
	while (++i < basic->n_philo)
	{
		if (i % 2 != 0)
		{
			status |= pthread_create(&basic->philo[i].thread_id,
					NULL, &philo, &basic->philo[i]);
			usleep(200);
		}
	}
	return (status);
}
