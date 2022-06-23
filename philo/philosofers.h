/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 02:36:09 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/23 20:04:15 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOFERS_H
# define PHILOSOFERS_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;


typedef struct s_philo
{
	int			index;
	int			time_last_eat;
    int			time_to_eat;
	int			time_to_sleep;
	int			ate_counter;
    int         work_time;
    t_mutex		*print;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
    t_thread	thread_id;

}	t_philo;

typedef struct s_info
{
	int				n_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				must_to_eat;
    int             work_time;
    int			    ate_counter;
	t_thread		*thread;
    t_mutex			*print;
    t_philo         *philo;
    t_mutex         *forks;
	t_thread		*spectator;
}	t_info;

int get_time(void);
int initialization(int argc, char **argv, t_info *basic);
int	ft_atoi(const char *str);

#endif