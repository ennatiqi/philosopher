/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:49:05 by rennatiq          #+#    #+#             */
/*   Updated: 2023/06/01 18:20:19 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	stop_get(t_philo *philo)
{
	pthread_mutex_lock(&philo->stop_thr);
	if (philo->stop)
	{
		pthread_mutex_unlock(&philo->stop_thr);
		return (1);
	}
	pthread_mutex_unlock(&philo->stop_thr);
	return (0);
}

void	ft_one_philo(t_philo *philo)
{
	print_pro(philo, 1, "is thinking");
	pthread_mutex_lock(&philo->forks[0]);
	if (stop_get(philo))
		return ;
	print_pro(philo, 1, "has taken a fork");
	while (1)
	{
		if (stop_get(philo))
			return ;
	}
}

void	*thread_function(void *phi)
{
	t_info	*info;
	t_philo	*philo;
	int		id;

	info = (t_info *)phi;
	philo = info->philo;
	id = info->id;
	if (philo->num_philo == 1)
	{
		ft_one_philo(philo);
		return (NULL);
	}
	while (1)
	{
		if (stop_get(philo))
			break ;
		ft_think(philo, id);
		if (stop_get(philo))
			break ;
		ft_eat(philo, id);
		if (stop_get(philo))
			break ;
		ft_sleep(philo, id);
		if (stop_get(philo))
			break ;
	}
	return (NULL);
}

void	join_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_philo)
	{
		if (pthread_join((philo->thread_info[i].thread), NULL) != 0)
		{
			return ;
		}
		i++;
	}
}

void	nano_sleep(t_philo *philo, int time_to_sleep)
{
	size_t	time;

	time = ft_get_time();
	while (ft_get_time() - time < (size_t)time_to_sleep)
	{
		if (stop_get(philo))
			break ;
		usleep(100);
	}
}
