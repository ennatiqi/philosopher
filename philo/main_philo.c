/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:55:08 by rennatiq          #+#    #+#             */
/*   Updated: 2023/02/27 15:05:27 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	generate_thread(t_philo	*philo)
{
	int		i;

	i = 0;
	while (i < philo->num_philo)
	{
		if (pthread_create(&philo->thread_info[i].thread, NULL,
				thread_function, &philo->thread_info[i]) != 0)
		{
			ft_error("Thread creation failed");
			return (1);
		}
		i++;
	}
	return (0);
}

int death_note(t_philo	*philo)
{
	size_t	time;
	int i = 0;

	while(i < philo->num_philo)
	{
		pthread_mutex_lock(&philo->koka);
		time = ft_get_time() - philo->start_time - philo->thread_info[i].last_eat_time;
		pthread_mutex_unlock(&philo->koka);
		if ((size_t)philo->time_to_die < time)
		{
			print_pro(philo, i + 1, "died");
			des_mutex(philo);
			return (1);
		}
		i++;
	}
	i = 0;
	if (philo->time_must_eat != -1)
	{
		while (i < philo->num_philo)
		{
			if (philo->thread_info[i].eat_times < philo->time_must_eat)
				break ;
			i++;
		}
		if (i == philo->num_philo)
		{
			des_mutex(philo);
		}
	}
	return 0;
}



int	death(t_philo	*philo)
{
	while (1)
	{
		if (death_note(philo))
		 	break ;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac != 6 && ac != 5)
	{
		ft_error("try to put 4 ot 5 args");
		return (1);
	}
	philo = first_step(av, ac);
	if (!philo)
		return (1);
	if (generate_thread(philo))
	{
		ft_error("Thread creation failed");
		return (1);
	}
	if (death(philo))
		return (0);
	return (0);
}