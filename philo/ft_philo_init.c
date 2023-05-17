/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:34:37 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/17 10:12:46 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

t_philo	*init_args(char **av)
{
	int		num_philo;
	t_philo	*philo;

	num_philo = ft_atoi(av[1]);
	philo = malloc(sizeof(t_philo));
	philo->num_philo = num_philo;
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		philo->time_must_eat = ft_atoi(av[5]);
	}
	else
		philo->time_must_eat = -1;
	philo->start_time = ft_get_time();
	return (philo);
}

void	thread_info_init_fork(t_philo *philo)
{
	int	i;

	i = 0;
	philo->forks = malloc(philo->num_philo * sizeof(pthread_mutex_t));
	philo->thread_info = (t_info *)malloc(philo->num_philo * sizeof(t_info));
	while (i < philo->num_philo)
	{
		philo->thread_info[i].philo = philo;
		philo->thread_info[i].eat_times = 0;
		philo->thread_info[i].last_eat_time = 0;
		philo->thread_info[i].id = i;
		i++;
	}
	i = 0;
	while (i < philo->num_philo)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo->koka, NULL);
	pthread_mutex_init(&philo->print, NULL);
	pthread_mutex_init(&philo->stop_thr, NULL);
}

void	des_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_philo)
	{
		pthread_mutex_destroy(&philo->forks[i]);
		i++;
	}
	// pthread_mutex_destroy(&philo->koka);
	// pthread_mutex_destroy(&philo->print);
	// pthread_mutex_destroy(&philo->stop);
	i = 0;
	while (i < philo->num_philo)
	{
		pthread_detach(philo->thread_info[i].thread);
		i++;
	}
	ft_free_pro(philo, philo->forks, philo->thread_info);
}
