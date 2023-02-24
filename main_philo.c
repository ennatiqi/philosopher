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

unsigned long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void *thread_function(void *phi)
{
	t_info	*info;
	int		id;

	info = (t_info *)phi;
	t_philo *philo;
	philo = info->philo;
	id = info->id;
	while(1) //aywgaf ila chiwa7d mat //awla sala time //
	{
		ft_eat(info,id);
		ft_sleep(info,id);
		ft_think(info,id);
		//printf("%d  \n",id);
	}
	return (NULL);
}

/* void init_args(t_philo *philo,char **av)
{

	while(i < num_philo)
	{
		philo->thread_info.time_must_eat = (unsigned long)ft_atoi(av[2]);
		philo->thread_info.time_to_die =  (unsigned long)ft_atoi(av[3]);
		philo->thread_info.time_to_eat =  (unsigned long)ft_atoi(av[4]);
		philo->thread_info.time_to_sleep =  (unsigned long)ft_atoi(av[5]);
		i++;
	}
} */

int main(int ac, char **av)
{
	if (ac != 6)
		return 1;
	
	
	int num_philo;
	t_philo *philo; 

	
	num_philo = ft_atoi(av[1]);
	
	philo = malloc(sizeof(t_philo));
	philo->thread_info[i].num_philo = num_philo;
	philo->thread_info[i].time_must_eat = (unsigned long)ft_atoi(av[2]);
	philo->thread_info[i].time_to_die =  (unsigned long)ft_atoi(av[3]);
	philo->thread_info[i].time_to_eat =  (unsigned long)ft_atoi(av[4]);
	philo->thread_info[i].time_to_sleep =  (unsigned long)ft_atoi(av[5]);
		
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
	i = 0;
	 while (i < num_philo)
	{
		pthread_mutex_destroy(&philo->forks[i] );
		i++;
	}    
}