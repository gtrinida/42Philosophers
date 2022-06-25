/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:40:22 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/25 20:04:35 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

typedef struct s_philo
{
	t_thread	thread_id;
	int			index;
	int			ate_last_time;
	int			time_to_sleep;
	int			time_to_eat;
	int			start_time;
	int			eat_counter;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	t_mutex		*print;
}	t_philo;

typedef struct s_basic
{
	int				start_time;
	int				n_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				eat_count;
	t_mutex			*print;
	t_philo			*philo;
	t_mutex			*forks;
}	t_basic;

int		destroy_threads(t_basic *basic);
int		get_time(void);
int		ft_atoi(const char *str);
int		threads_init(t_basic *basic);
int		basic_init(int argc, char **argv, t_basic *basic);
void	philo_init(t_basic *basic);
void	ft_usleep(size_t milliseconds);

#endif