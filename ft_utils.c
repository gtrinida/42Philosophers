/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:40:37 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/22 22:40:40 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

int	ft_timestamp(void)
{
	struct timeval	time;
	size_t			milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = time.tv_sec * 1000;
	milliseconds += time.tv_usec / 1000;
	return ((int) milliseconds);
}

void	ft_sleep(size_t milliseconds)
{
	size_t	start_time;

	start_time = ft_timestamp();
	while (ft_timestamp() - start_time < milliseconds)
		usleep(50);
}

int	ft_throw(const char *error, int code)
{
	printf("%s: ", PROGRAM_NAME);
	printf("%s\n", error);
	return (code);
}
