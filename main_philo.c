/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:55:08 by rennatiq          #+#    #+#             */
/*   Updated: 2023/02/21 17:23:37 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void *thread_function(void *phi)
{
	t_info	*info;
	int		id;

	info = (t_info *)phi;
	t_philo *philo;
	philo = info->philo;
	id = info->id;
	while(philo->death_note == 0) //(philo->time_to_die < info->last_eat_time)
	{
		ft_eat(philo,id);
		ft_sleep(philo,id);
		ft_think(philo,id);
	}
	return (NULL);
}

int main(int ac, char **av)
{
	if (ac != 6)
		return 1;
	
	
	int num_philo;
	t_philo *philo; 

	
	num_philo = ft_atoi(av[1]);
	
	philo = malloc(sizeof(t_philo));
	philo->num_philo = num_philo;
	philo->time_must_eat = (unsigned long)ft_atoi(av[2]);
	philo->time_to_die =  (unsigned long)ft_atoi(av[3]);
	philo->time_to_eat =  (unsigned long)ft_atoi(av[4]);
	philo->time_to_sleep =  (unsigned long)ft_atoi(av[5]);
	philo->death_note = 0;
		
	int i = 0;
	philo->start_time = ft_get_time();
	philo->forks = (pthread_mutex_t *)malloc(num_philo * sizeof(pthread_mutex_t));
	philo->thread_info = (t_info *)malloc(num_philo * sizeof(t_info));
	while(i < num_philo)
	{
		philo->thread_info[i].philo = philo;
		i++;
	}
	i = 0;


	while (i < num_philo)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		philo->thread_info[i].id = i;
		i++;
	}
	i = 0;

	while (i < num_philo)
	{

		if (pthread_create(&philo->thread_info[i].thread, NULL, thread_function, &philo->thread_info[i]) != 0)
		{
			perror("Thread creation failed");
			return 1;
		}
		i++;
	}
	i = 0;
	while (i < num_philo)
	{
		if (pthread_join((philo->thread_info[i].thread), NULL) != 0)
		{
			perror("Thread creation failed");
			return 1;
		}
		i++;
	}
	
}