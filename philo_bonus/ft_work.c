/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_work.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:50:56 by rennatiq          #+#    #+#             */
/*   Updated: 2023/06/02 16:01:25 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	print_pro(t_philo *philo, int id, char *str)
{
	sem_wait(philo->print);
	printf("%lu %d %s\n", ft_get_time() - philo->start_time, id, str);
	sem_post(philo->print);
}

void	ft_eat(t_philo *philo, int id)
{
	sem_wait(philo->forks);
	print_pro(philo, id + 1, "has taken a fork");
	sem_wait(philo->forks);
	print_pro(philo, id + 1, "has taken a fork");
	print_pro(philo, id + 1, "is eating");
	sem_wait(philo->koka);
	philo->thread_info[id].last_eat_time = ft_get_time() - philo->start_time;
	sem_post(philo->koka);
	nano_sleep(philo->time_to_eat);
	sem_wait(philo->koka2);
	philo->thread_info[id].eat_times++;
	sem_post(philo->koka2);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

int	ft_think(t_philo *philo, int id)
{
	print_pro(philo, id + 1, "is thinking");
	return (1);
}

void	ft_sleep(t_philo *philo, int id)
{
	print_pro(philo, id + 1, "is sleeping");
	nano_sleep(philo->time_to_sleep);
}

size_t	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
