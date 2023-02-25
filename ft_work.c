/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_work.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:50:56 by rennatiq          #+#    #+#             */
/*   Updated: 2023/02/25 14:43:41 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void test_death(t_philo *philo, int id)
{
	unsigned long time;

	if (philo->time_to_die < philo->thread_info[id].last_eat_time)
	{
		time = ft_get_time() - philo->start_time;
		printf("%lums %d is death\n", time, id + 1);
		des_mutex(philo);
		exit(0);
		//philo->death_note = 1;
	}
	if (philo->thread_info[id].eat_times == philo->num_philo)
	{
		des_mutex(philo);
		exit(0);
	}
}

void ft_eat(t_philo *philo, int id)
{
	unsigned long time;

	pthread_mutex_lock(&philo->forks[id]);
	time = ft_get_time() - philo->start_time;
	printf("%lums %d taking a right fork\n",time, id + 1);
	pthread_mutex_lock(&philo->forks[(id + 1) % philo->num_philo]);
	time = ft_get_time() - philo->start_time;
	printf("%lums %d taking a left fork\n",time, id + 1);
	printf("%lums %d is eating\n",time, id + 1);
	usleep(1000 * philo->time_must_eat);
	philo->thread_info[id].last_eat_time = ft_get_time() - philo->start_time;
	pthread_mutex_unlock(&philo->forks[id]);
	pthread_mutex_unlock(&philo->forks[(id + 1) % philo->num_philo]);
}

int ft_think(t_philo *philo, int id)
{
	unsigned long time;

	time = ft_get_time() - philo->start_time;
	printf("%lums %d is thinking\n",time, id + 1);
	test_death(philo,id);
	return 1;
}

void ft_sleep(t_philo *philo, int id)
{
	unsigned long time = ft_get_time() - philo->start_time;
	printf("%lums %d is sleeping\n",time, id + 1);
	usleep(1000 * philo->time_to_sleep);
}

unsigned long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
