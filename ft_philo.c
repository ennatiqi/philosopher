/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:49:05 by rennatiq          #+#    #+#             */
/*   Updated: 2023/02/26 15:04:25 by rennatiq         ###   ########.fr       */
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
	if (philo->num_philo == 1)
	{
		printf("0ms %d died\n", id + 1);
		des_mutex(philo);
		exit(0);
	}
	if (id % 2 != 0)
		usleep(100);
	while (1)
	{
		ft_eat(philo, id);
		ft_sleep(philo, id);
		ft_think(philo, id);
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
			perror("Thread creation failed");
			exit (1);
		}
		i++;
	}
}
