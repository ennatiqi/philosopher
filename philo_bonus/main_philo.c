/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:07:38 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/17 09:55:49 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	death_note(t_philo	*philo, int id)
{
	size_t	time;

	while (1)
	{
		sem_wait(philo->koka);
		time = ft_get_time() - philo->start_time
			- philo->thread_info[id].last_eat_time;
		sem_post(philo->koka);
		if ((size_t)philo->time_to_die < time)
		{
			sem_wait(philo->print);
			printf("%lu %d died\n", ft_get_time() - philo->start_time, id + 1);
			exit (1);
		}
		if (philo->time_must_eat != -1)
		{
			if (philo->thread_info[id].eat_times >= philo->time_must_eat)
				exit (1);
		}
	}
}

void	kill_processes(t_philo *philo, int *stat)
{
	int	i;
	int	status;

	i = 0;
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	if (status == 1)
	{
		while (i < philo->num_philo)
		{
			kill(stat[i], SIGKILL);
			i++;
		}
		des_mutex(philo);
		return ;
	}
}

void	creat_processes(t_philo *philo)
{
	int	i;
	int	status;
	int	*stat;

	i = 0;
	stat = malloc(sizeof(int) * philo->num_philo);
	while (i < philo->num_philo)
	{
		if (i % 2 == 0)
			usleep(100);
		stat[i] = fork();
		if (stat[i] == 0)
		{
			if (pthread_create(&philo->thread_info[i].thread, NULL,
					&thread_function, &philo->thread_info[i]))
			{
				ft_error("Thread creation failed");
				exit (1);
			}
			death_note(philo, i);
		}
		i++;
	}
	kill_processes(philo, stat);
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
	creat_processes(philo);
	return (0);
}
