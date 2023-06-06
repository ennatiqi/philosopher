/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:07:38 by rennatiq          #+#    #+#             */
/*   Updated: 2023/06/06 11:15:56 by rennatiq         ###   ########.fr       */
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
		// sem_wait(philo->koka2);
		// if (philo->time_must_eat != -1)
		// {
		// 	sem_post(philo->koka2);
		// 	if (philo->thread_info[id].eat_times >= philo->time_must_eat)
		// 		exit (1);
		// }
		// sem_post(philo->koka2);
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

void *check_eats(void *phi)
{
	t_philo	*philo;
	int i = 0;

	philo = (t_philo *)phi;
	if (philo->time_must_eat == -1)
		return NULL;
	while (i < philo->num_philo)
	{
		sem_wait(philo->est_times);
		i++;
	}
	i = 0;
	while (i < philo->num_philo)
	{
		kill(philo->stat[i], SIGKILL);
		i++;
	}
	des_mutex(philo);
	free(philo->stat);
	exit(0);
	
}

void	creat_processes(t_philo *philo)
{
	int	i;

	i = 0;
	philo->stat = malloc(sizeof(int) * philo->num_philo);
	while (i < philo->num_philo)
	{
		philo->stat[i] = fork();
		if (philo->stat[i] == 0)
		{
			if (i % 2 == 0)
				usleep(100);
			if (pthread_create(&philo->thread_info[i].thread, NULL,
					&thread_function, &philo->thread_info[i]))
			{
				exit (1);
			}
			death_note(philo, i);
		}
		i++;
	}
	if (pthread_create(&philo->eating, NULL,
			&check_eats, &philo))
		exit (1);
	kill_processes(philo, philo->stat);
	free(philo->stat);
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
