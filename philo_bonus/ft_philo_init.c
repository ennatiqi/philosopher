/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:34:37 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/17 09:56:26 by rennatiq         ###   ########.fr       */
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
	philo->thread_info = (t_info *)malloc(philo->num_philo * sizeof(t_info));
	while (i < philo->num_philo)
	{
		philo->thread_info[i].philo = philo;
		philo->thread_info[i].eat_times = 0;
		philo->thread_info[i].last_eat_time = 0;
		philo->thread_info[i].id = i;
		i++;
	}
	sem_unlink("forks");
	sem_unlink("koka");
	sem_unlink("print");
	philo->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, philo->num_philo);
	philo->koka = sem_open("koka", O_CREAT | O_EXCL, 0644, 1);
	philo->print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
}

void	des_mutex(t_philo *philo)
{
	sem_close(philo->forks);
	sem_unlink("/forks");
	sem_close(philo->koka);
	sem_unlink("/koka");
	sem_close(philo->print);
	sem_unlink("/print");
	ft_free_pro(philo, philo->thread_info);
}
