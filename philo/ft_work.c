/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_work.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:50:56 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/16 08:57:32 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void print_pro(t_philo *philo,int id, char *str)
{
	pthread_mutex_lock(&philo->print);
	printf("%lu %d %s\n",ft_get_time() - philo->start_time , id, str);
	pthread_mutex_unlock(&philo->print);
}

void	ft_eat(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->forks[id]);
	print_pro(philo, id + 1, "has taken a fork");
	pthread_mutex_lock(&philo->forks[(id + 1) % philo->num_philo]);
	print_pro(philo, id + 1, "has taken a fork");
	print_pro(philo, id + 1, "is eating");
	pthread_mutex_lock(&philo->koka);
	philo->thread_info[id].last_eat_time = ft_get_time() - philo->start_time;
	pthread_mutex_unlock(&philo->koka);
	nano_sleep(philo->time_to_eat);
	philo->thread_info[id].eat_times++;
	pthread_mutex_unlock(&philo->forks[id]);
	pthread_mutex_unlock(&philo->forks[(id + 1) % philo->num_philo]);
}

int	ft_think(t_philo *philo, int id)
{
	print_pro(philo, id + 1, "is thinking");
	return (1);
}

void	ft_sleep(t_philo *philo, int id)
{
	print_pro(philo,id + 1, "is sleeping");
	nano_sleep(philo->time_to_sleep);
}

size_t	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
