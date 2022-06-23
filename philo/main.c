/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:04:35 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/23 21:05:20 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

void	sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
    printf("%d %d is sleeping\n", get_time() - philo->work_time, philo->index);
    pthread_mutex_unlock(philo->print);
	usleep(philo->time_to_sleep);
}

void    eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->print);
	printf("%d %d has taken a fork\n", get_time() - philo->work_time, philo->index + 1);
	pthread_mutex_unlock(philo->print);
    pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->print);
	printf("%d %d has taken a fork\n", get_time() - philo->work_time, philo->index + 1);
	pthread_mutex_unlock(philo->print);
    philo->time_last_eat = get_time() - philo->work_time;
	pthread_mutex_lock(philo->print);
    printf("%d %d is eating\n", get_time() - philo->work_time, philo->index);
    philo->ate_counter++;
    pthread_mutex_unlock(philo->print);
	usleep(philo->time_to_eat);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

int	spectator(t_info *basic)
{
    int	i;

	i = 0;
	while (i < basic->n_philo)
	{
        if (basic->philo[i].ate_counter > 0 && basic->ate_counter > -1
				|| basic->philo[i].ate_counter > -1 && basic->ate_counter == -1)
		{
			if (get_time() - basic->philo[i].time_last_eat >= basic->time_to_die)
			{
				thread_mutex_lock(basic->print);
				if (basic->philo[i].ate_counter < basic->ate_counter)
					printf ("%d %d died\n", get_time()- basic->philo[i].work_time, i + 1);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
void    philo(void *arg)
{
    t_philo *tmp;
    
    tmp = (t_philo *)arg;
    if (tmp->index % 2)
    {
        usleep(tmp->time_to_eat);
    }
    while (1)
    {
        eat(tmp);
        sleep(tmp);
        pthread_mutex_lock(tmp->print);
        printf("%d %d is thinking\n", get_time() - tmp->work_time, tmp->index);
        pthread_mutex_unlock(tmp->print);
    }
}

int start_threads(t_info *basic)
{
    int i;
    
    i = 0;
    while (i < basic->n_philo)
    {
        pthread_create(&basic->thread[i], NULL, philo, &basic->philo[i]);
        i++;
    }
    i = 0;
    while (i < basic->n_philo)
    {
        pthread_detach(basic->thread[i]);
        i++;
    }
}

void	ft_destroy(t_info *basic)
{
	int	i;

	i = 0;
	while (i < basic->n_philo)
	{
		pthread_mutex_destroy(&basic->forks[i]);
		i++;
	}
	pthread_mutex_destroy(basic->print);
}

int main(int argc, char **argv)
{
    t_info *basic;

    basic = malloc(sizeof(t_info));
    if (argc != 5 && argc != 6)
    {
        printf("Invalid number of arguments!\n");
        return (0);
    }    
    if (!initialization(argc, argv, basic))
        return (0);
    start_threads(basic);
    while (1)
    {
        if (!spectator(basic))
        {
            ft_destroy(basic);
        }
    }
    return (1);
}
