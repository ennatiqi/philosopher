/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:55:08 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/29 09:50:12 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	generate_thread(t_philo	*philo)
{
	int		i;

	i = 0;
	while (i < philo->num_philo)
	{
		if (i % 2 != 0)
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

void	stop_set(t_philo	*philo)
{
	pthread_mutex_lock(&philo->stop_thr);
	philo->stop = 1;
	pthread_mutex_unlock(&philo->stop_thr);
}

int	eat_times(t_philo	*philo)
{
	int	i;

	i = 0;
	if (philo->time_must_eat != -1)
	{
		while (i < philo->num_philo)
		{
			pthread_mutex_lock(&philo->eat_time);
			if (philo->thread_info[i].eat_times < philo->time_must_eat)
			{
				pthread_mutex_unlock(&philo->eat_time);
				break ;
			}
			pthread_mutex_unlock(&philo->eat_time);
			i++;
		}
		if (i == philo->num_philo)
		{
			stop_set(philo);
			return (1);
		}
	}
	return (0);
}

int	death_note(t_philo	*philo)
{
	size_t	time;
	int		i;

	i = 0;
	while (i < philo->num_philo)
	{
		pthread_mutex_lock(&philo->koka);
		time = ft_get_time() - philo->start_time
			- philo->thread_info[i].last_eat_time;
		pthread_mutex_unlock(&philo->koka);
		if ((size_t)philo->time_to_die < time)
		{
			stop_set(philo);
			pthread_mutex_lock(&philo->print);
			printf("%lu %d died\n", ft_get_time() - philo->start_time, i + 1);
			return (1);
		}
		i++;
	}
	if (eat_times(philo))
		return (1);
	return (0);
}

void	death(t_philo	*philo)
{
	while (1)
	{
		if (death_note(philo))
			break ;
	}
	return ;
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
	death(philo);
	des_mutex(philo);
	return (0);
}
