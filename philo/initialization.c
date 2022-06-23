/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 03:08:37 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/23 18:39:32 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

int	ft_isdight(int character)
{
	return (character >= '0' && character <= '9');
}

int parser(int argc, char **argv)
{
    int i;
    int j;

    j = 0;
    i = 1;
    while (i < argc)
    {
        while (argv[i][j])
        {
            if (!ft_isdight(argv[i][j]))
            {
                printf ("Invalid values!\n");
                return (0);
            }
            j++;
        }  
        j = 0;
        i++;
    }
    return (1);
}

void    millisec_to_microsec(t_info *basic)
{
    basic->time_to_die *= 1000;
    basic->time_to_eat *= 1000;
    basic->time_to_sleep *= 1000;  
}

int get_time(void)
{
    struct timeval  time;
    int             millisec;

    gettimeofday(&time, NULL);
    millisec = time.tv_sec * 1000;
    millisec += time.tv_usec / 1000; //колиечество милиосекунд
    //понимаем сколько прошло времени
    return (millisec);
}

int philo_init(t_info *basic)
{
    int i;

    i = 0;
    pthread_mutex_init(basic->print, NULL);
    while (i < basic->n_philo)
    {
        pthread_mutex_init(&basic->forks[i], NULL);
        i++;
    }
    i = 0;
	while (i < basic->n_philo)
	{
		basic->philo[i].index = i + 1;
		basic->philo[i].time_to_eat = basic->time_to_eat;
		basic->philo[i].time_to_sleep = basic->time_to_sleep;
		basic->philo[i].time_last_eat = 0;
		basic->philo[i].left_fork = &basic->forks[i]; //почему тут & и что за расчёты у правой вилки
		basic->philo[i].right_fork = &basic->forks[(i + 1) % basic->n_philo];
		basic->philo[i].work_time = basic->work_time;
		basic->philo[i].print = basic->print;
		basic->philo[i].ate_counter = basic->ate_counter;
        i++;
    }
}

int basic_init(t_info *basic, int argc, char **argv)
{
    if (!parser(argc, argv))
        return (0);
    if (basic->n_philo = ft_atoi(argv[1]) == 0)
        return (0);
    basic->time_to_die = ft_atoi(argv[2]);
    basic->time_to_eat = ft_atoi(argv[3]);
    basic->time_to_sleep = ft_atoi(argv[4]);
    millisec_to_microsec(basic);
    if (argc != 6)
        basic->must_to_eat = -1;
    else
        basic->must_to_eat = ft_atoi(argv[5]);
    basic->forks = malloc(sizeof(t_mutex) * basic->n_philo);
    basic->philo = malloc(sizeof(t_philo) * basic->n_philo);
    basic->thread = malloc(sizeof(t_thread) * basic->n_philo);
    basic->work_time = get_time();
    philo_init(basic);
    return (1);
}

int initialization(int argc, char **argv, t_info *basic)
{
    if (!basic_init(basic, argc, argv))
        return (0);
    return (1);
}