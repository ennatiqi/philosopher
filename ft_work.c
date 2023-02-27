/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_work.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:50:56 by rennatiq          #+#    #+#             */
/*   Updated: 2023/02/27 14:46:09 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	test_death(t_philo *philo, int id)
{
	unsigned long	time;

	if (philo->thread_info[id].last_eat_time != 0)
		time = ft_get_time() - philo->thread_info[id].last_eat_time;
	else
		time = ft_get_time() - philo->start_time;
	if ((unsigned long)philo->time_to_die < time)
	{
		philo->death_note = 1;
		time = ft_get_time() - philo->start_time;
		printf("%lu %d died\n", time, id + 1);
		des_mutex(philo);
		return (1);
	}
	if (philo->thread_info[id].eat_times == philo->time_must_eat)
	{
		des_mutex(philo);
		return (1);
	}
	return (0);
}

void	ft_eat(t_philo *philo, int id)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->forks[id]);
	time = ft_get_time() - philo->start_time;
	printf("%lu %d has taken a fork\n", time, id + 1);
	pthread_mutex_lock(&philo->forks[(id + 1) % philo->num_philo]);
	time = ft_get_time() - philo->start_time;
	printf("%lu %d has taken a fork\n", time, id + 1);
	printf("%lu %d is eating\n", time, id + 1);
	philo->thread_info[id].last_eat_time = ft_get_time();
	nano_sleep(philo->time_to_eat);
	philo->thread_info[id].eat_times++;
	pthread_mutex_unlock(&philo->forks[id]);
	pthread_mutex_unlock(&philo->forks[(id + 1) % philo->num_philo]);
}

int	ft_think(t_philo *philo, int id)
{
	unsigned long	time;

	time = ft_get_time() - philo->start_time;
	printf("%lu %d is thinking\n", time, id + 1);
	return (1);
}

void	ft_sleep(t_philo *philo, int id)
{
	unsigned long	time;

	time = ft_get_time() - philo->start_time;
	printf("%lu %d is sleeping\n", time, id + 1);
	nano_sleep(philo->time_to_sleep);
}

unsigned long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
