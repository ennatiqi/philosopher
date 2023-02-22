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
	//fork -> eat -> sleep -> thinking
	philo_t	*philo;

	philo = (philo_t *)phi;
	/* while(1) //aywgaf ila chiwa7d mat //awla sala time //
	{
		eat(philo,philo->id);
		slep(philo,philo->id);
		think(philo,philo->id);
	} */
	printf("%d  ",philo->id);
	return (NULL);
}

int main(int ac, char **av)
{
	/* if (ac != 7)
		return 1; */
	
	
	int num_philo;
	philo_t *philo; 

	
	num_philo = ft_atoi(av[1]);
	
	philo = malloc(sizeof(philo_t));
	int i = 0;
	while (i < num_philo)
	{
		philo->time_must_eat = ft_atoi(av[2]);
		philo->time_to_die = ft_atoi(av[3]);
		philo->time_to_eat = ft_atoi(av[4]);
		philo->time_to_sleep = ft_atoi(av[5]);
		i++;
	}
	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_init(&philo->fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < num_philo)
	{
		philo->id = i + 1;
		if (pthread_create(&philo->philo[i], NULL, thread_function, philo) != 0)
		{
			perror("Thread creation failed");
			return 1;
		}
		i++;
	}
	i = 0;
	while (i < num_philo)
	{
		if (pthread_join(philo->philo[i], NULL) != 0)
		{
			perror("Thread creation failed");
			return 1;
		}
		i++;
	}
	i = 0;
	 while (i < num_philo)
	{
		pthread_mutex_destroy(&philo->fork[i] );
		i++;
	}    
}