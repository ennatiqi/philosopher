/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:55:08 by rennatiq          #+#    #+#             */
/*   Updated: 2023/02/26 13:52:33 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	main(int ac, char **av)
{
	int		i;
	t_philo	*philo;

	if (ac != 6 && ac != 5)
		return (1);
	if (check_args(av, ac))
		return (1);
	philo = init_args(av);
	thread_info_init_fork(philo);
	i = 0;
	while (i < philo->num_philo)
	{
		if (pthread_create(&philo->thread_info[i].thread, NULL,
				thread_function, &philo->thread_info[i]) != 0)
		{
			perror("Thread creation failed");
			return (1);
		}
		i++;
	}
	join_threads(philo);
	return (0);
}
