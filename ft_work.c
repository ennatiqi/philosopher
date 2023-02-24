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
void test_death(t_philo *philo, int id)
{
	if (philo->time_to_die < philo->thread_info[id].last_eat_time)
	{
		printf("%d is death\n", id + 1);
		died(philo);
		exit(0);
		//philo->death_note = 1;
	}
}



void ft_eat(t_philo *philo, int id)
{
	unsigned long time = ft_get_time() - philo->start_time;
	pthread_mutex_lock(&philo->forks[id]);
	printf("%lums -> %d taking a right fork\n",time, id + 1);
	pthread_mutex_lock(&philo->forks[(id + 1) % philo->num_philo]);
	printf("%lums -> %d taking a left fork\n",time, id + 1);
	printf("%lums -> %d is eating\n",time, id + 1);
	usleep(1000 * philo->time_must_eat);
	philo->thread_info[id].last_eat_time = ft_get_time() - philo->start_time;
	pthread_mutex_unlock(&philo->forks[id]);
	pthread_mutex_unlock(&philo->forks[(id + 1) % philo->num_philo]);
}

int ft_think(t_philo *philo, int id)
{
	unsigned long time = ft_get_time() - philo->start_time;

	printf("%lums -> %d is thinking\n",time, id + 1);
	test_death(philo,id);
	return 1;
}

void ft_sleep(t_philo *philo, int id)
{
	unsigned long time = ft_get_time() - philo->start_time;
	printf("%lums -> %d is sleeping\n",time, id + 1);
	usleep(1000 * philo->time_to_sleep);
	//test_death(philo,id);
}

unsigned long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void died(t_philo *philo)
{
	int i = 0;
	 while (i < philo->num_philo)
	{
		pthread_mutex_destroy(&philo->forks[i] );
		i++;
	}    
}