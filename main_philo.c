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
		if (i % 2 == 0)
			usleep(100);
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

int	death(t_philo	*philo)
{
	int		i;

	i = 0;
	while (philo->death_note == 0)
	{
		if (test_death(philo, philo->thread_info[i].id) == 1)
			return (1);
		i++;
		if (i > philo->num_philo)
			i = 0;
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
	join_threads(philo);
	return (0);
}
