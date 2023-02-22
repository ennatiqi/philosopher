/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_work.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:50:56 by rennatiq          #+#    #+#             */
/*   Updated: 2023/02/21 16:01:52 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void eat(philo_t *philo, int id)
{
	pthread_mutex_lock(&philo->fork[id]);
	pthread_mutex_lock(&philo->fork[id + 1]);
	printf("philo %d eating\n", id);
	usleep(1000 * philo->time_must_eat);
	pthread_mutex_unlock(&philo->fork[id]);
	pthread_mutex_unlock(&philo->fork[id + 1]);
}

int think(philo_t *philo, int id)
{
	printf("philo %d thinking\n", id);
	//ila b9a kayfkar ta mat
	 //usleep(1000 * philo->time_to_sleep);
	 return 1;
}

void slep(philo_t *philo, int id)
{
	printf("philo %d sleeping\n", id);
	usleep(1000 * philo->time_to_sleep);
}