/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:40:29 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/25 13:34:07 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_take_forks(t_philosopher *philosopher)
{
	int	time;

	pthread_mutex_lock(philosopher->left_fork);
	time = ft_timestamp() - philosopher->start_time;
	pthread_mutex_lock(philosopher->print);
	printf("%d %d \033[0;42mhas taken a fork\033[0m\n",
		time, philosopher->index);
	pthread_mutex_unlock(philosopher->print);
	pthread_mutex_lock(philosopher->right_fork);
	time = ft_timestamp() - philosopher->start_time;
	pthread_mutex_lock(philosopher->print);
	printf("%d %d \033[0;41mhas taken a fork\033[0m\n",
		time, philosopher->index);
	pthread_mutex_unlock(philosopher->print);
}

void	ft_action_eat(t_philosopher *philosopher)
{
	philosopher->ate_last_time = ft_timestamp() - philosopher->start_time;
	pthread_mutex_lock(philosopher->print);
	printf("%d %d is eating\n", philosopher->ate_last_time,
		philosopher->index);
	pthread_mutex_unlock(philosopher->print);
	ft_sleep(philosopher->eat_time);
	pthread_mutex_unlock(philosopher->right_fork);
	pthread_mutex_unlock(philosopher->left_fork);
}

void	ft_action_sleep(t_philosopher *philosopher)
{
	int	time;

	time = ft_timestamp() - philosopher->start_time;
	pthread_mutex_lock(philosopher->print);
	printf("%d %d is sleeping\n", time, philosopher->index);
	pthread_mutex_unlock(philosopher->print);
	ft_sleep(philosopher->sleep_time);
	time = ft_timestamp() - philosopher->start_time;
	pthread_mutex_lock(philosopher->print);
	printf("%d %d is thinking\n", time, philosopher->index);
	pthread_mutex_unlock(philosopher->print);
}

void	*ft_philosophy(void *ph_ptr)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)ph_ptr;
	pthread_detach(philosopher->thread_id);
	while (philosopher->eat_counter != 0)
	{
		ft_take_forks(philosopher);
		ft_action_eat(philosopher);
		ft_action_sleep(philosopher);
		if (philosopher->eat_counter > 0)
			philosopher->eat_counter--;
		if (!philosopher->eat_counter)
			return (0);
	}
	return (0);
}

int	threads_init(t_env *env)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < env->n_philosophers)
	{
		if (i % 2 == 0)
		{
			status |= pthread_create(&env->philosophers[i].thread_id,
					NULL, &ft_philosophy, &env->philosophers[i]);
			usleep(135);
		}
	}
	i = -1;
	while (++i < env->n_philosophers)
	{
		if (i % 2 != 0)
		{
			status |= pthread_create(&env->philosophers[i].thread_id,
					NULL, &ft_philosophy, &env->philosophers[i]);
			usleep(135);
		}
	}
	return (status);
}
