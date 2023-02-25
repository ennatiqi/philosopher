/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:34:37 by rennatiq          #+#    #+#             */
/*   Updated: 2023/02/25 14:42:47 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

t_philo *init_args(char **av)
{
	int num_philo;
	t_philo *philo;

	num_philo = ft_atoi(av[1]);
	
	philo = malloc(sizeof(t_philo));
	philo->num_philo = num_philo;
	philo->time_to_die = (unsigned long)ft_atoi(av[2]);
	philo->time_to_eat =  (unsigned long)ft_atoi(av[3]);
	philo->time_to_sleep =  (unsigned long)ft_atoi(av[4]);
	philo->time_must_eat =  (unsigned long)ft_atoi(av[5]);
	philo->death_note = 0;
	philo->start_time = ft_get_time();
	return (philo);
}

void	thread_info_init_fork(t_philo *philo)
{
	int	i;

	i = 0;
	philo->forks = (pthread_mutex_t *)malloc(philo->num_philo * sizeof(pthread_mutex_t));
	philo->thread_info = (t_info *)malloc(philo->num_philo * sizeof(t_info));
	while(i < philo->num_philo)
	{
		philo->thread_info[i].philo = philo;
		philo->thread_info[i].eat_times = 0;
		i++;
	}
	i = 0;
	while (i < philo->num_philo)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		philo->thread_info[i].id = i;
		i++;
	}
}

void des_mutex(t_philo *philo)
{
	int i = 0;
	 while (i < philo->num_philo)
	{
		pthread_mutex_destroy(&philo->forks[i] );
		i++;
	}    
}