/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:55:08 by rennatiq          #+#    #+#             */
/*   Updated: 2023/02/26 15:34:07 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	main(int ac, char **av)
{
	int		i;
	t_philo	*philo;

	if (ac != 6 && ac != 5)
	{
		ft_error("try to put 4 ot 5 args");
		return (1);
	}
	if (check_args(av, ac))
	{
		ft_error("your args mast be integers");
		return (1);
	}
	philo = init_args(av);
	if (check_negativ(philo, av))
	{
		ft_error("your args mast be positive");
		return (1);
	}
	thread_info_init_fork(philo);
	i = 0;
	while (i < philo->num_philo)
	{
		if (pthread_create(&philo->thread_info[i].thread, NULL,
				thread_function, &philo->thread_info[i]) != 0)
		{
			ft_error("Thread creation failed");
			return (1);
		}
		usleep(100);
		i++;
	}
	while (philo->death_note == 0)
	{
		if (test_death(philo, philo->thread_info[i].id) == 1)
			return (0);
		i++;
		if (i > philo->num_philo)
			i = 0;
	}
	join_threads(philo);
	return (0);
}
