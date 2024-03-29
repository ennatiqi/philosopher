/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:49:05 by rennatiq          #+#    #+#             */
/*   Updated: 2023/06/06 09:52:45 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	*thread_function(void *phi)
{
	t_info	*info;
	t_philo	*philo;
	int		id;

	info = (t_info *)phi;
	philo = info->philo;
	id = info->id;
	if (philo->time_must_eat != -1)
		sem_wait(philo->est_times);
	if (id % 2 != 0)
		usleep(100);
	while (1)
	{
		ft_think(philo, id);
		ft_eat(philo, id);
		ft_sleep(philo, id);
	}
	return (NULL);
}

void	join_threads(t_philo	*philo)
{
	int	i;

	i = 0;
	while (i < philo->num_philo)
	{
		if (pthread_join((philo->thread_info[i].thread), NULL) != 0)
		{
			ft_error("Thread join failed");
			return ;
		}
		i++;
	}
}

void	nano_sleep(int time_to_sleep)
{
	size_t	time;

	time = ft_get_time();
	while (ft_get_time() - time < (size_t)time_to_sleep)
		usleep(100);
}
