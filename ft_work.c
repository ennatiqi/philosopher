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

void ft_eat(t_info *philo, int id)
{
	unsigned long time = ft_get_time() - philo->philo->start_time;
	pthread_mutex_lock(&philo->philo->forks[id]);
	pthread_mutex_lock(&philo->philo->forks[(id + 1) % philo->num_philo]);
	printf("%lums -> %d is eating\n",time, id + 1);
	philo->last_est_time = ft_get_time();
	usleep(1000 * philo->time_must_eat);
	pthread_mutex_unlock(&philo->philo->forks[id]);
	pthread_mutex_unlock(&philo->philo->forks[(id + 1) % philo->num_philo]);
}

int ft_think(t_info *philo, int id)
{
	unsigned long time = ft_get_time() - philo->philo->start_time;

	printf("%lums -> %d is thinking\n",time, id + 1);
	//ila b9a kayfkar ta mat
	return 1;
}

void ft_sleep(t_info *philo, int id)
{
	unsigned long time = ft_get_time() - philo->philo->start_time;
	printf("%lums -> %d is sleeping\n",time, id + 1);
	usleep(1000 * philo->time_must_eat);
}