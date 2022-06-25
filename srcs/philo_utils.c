/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:40:37 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/26 02:38:12 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_time(void)
{
	size_t			milisec;
	struct timeval	time;

	gettimeofday(&time, NULL);
	milisec = time.tv_sec * 1000;
	milisec += time.tv_usec / 1000;
	return ((int) milisec);
}

void	ft_usleep(size_t milisec)
{
	size_t	start_time;

	start_time = get_time();
	while (get_time() - start_time < milisec)
		usleep(100);
}
