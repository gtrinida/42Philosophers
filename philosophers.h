/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:40:22 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/25 13:33:00 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

// Constants
# define PROGRAM_NAME			"42philosophers"
# define EXIT_DEAD				0
# define ERROR_ARGS				"error: the specified arguments are invalid!"
# define ERROR_USAGE			"usage: [nbr_of_philosophers] [die_time] \
[eat_time] [sleep_time] [optional: number_of_times_each_philosopher_must_eat]"
# define ERROR_MALLOC			"error: not enough RAM!"
# define ERROR_CREATE_THREAD	"error: can't properly create threads!"

// Typedefs
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

// Structures
typedef struct s_philosopher
{
	t_thread	thread_id;
	int			index;
	int			ate_last_time;
	int			sleep_time;
	int			eat_time;
	int			start_time;
	int			eat_counter;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	t_mutex		*print;
}	t_philosopher;

typedef struct s_env
{
	int				start_time;
	int				n_philosophers;
	int				eat_time;
	int				sleep_time;
	int				die_time;
	int				eat_count;
	t_mutex			*print;
	t_philosopher	*philosophers;
	t_mutex			*forks;
}	t_env;

int		threads_init(t_env *env);
int		basic_init(int argc, char **argv, t_env *env);
void	philo_init(t_env *env);


// Main functions

// Utilities functions
int		ft_timestamp(void);
void	ft_sleep(size_t milliseconds);
int		ft_atoi(const char *str);
int		ft_throw(const char *error, int code);

#endif