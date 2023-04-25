#include "ft_philo.h"

void death_note(t_philo	*philo, int id)
{
	size_t	time;
	// int 	i;

	sem_wait(philo->koka);
	time = ft_get_time() - philo->start_time - philo->thread_info[id].last_eat_time;
	sem_post(philo->koka);
	if ((size_t)philo->time_to_die < time)
	{
		print_pro(philo, id + 1, "died");
		exit (1);
	}
	if (philo->time_must_eat != -1)
	{
		if (philo->thread_info[id].eat_times >= philo->time_must_eat)
		{
			exit (0);
		}
	}
}

void creat_processes(t_philo *philo)
{
    int i = 0;
	int status;
    int *stat;

    stat = malloc(sizeof(int) * philo->num_philo);
    while (i < philo->num_philo)
    {
        stat[i] = fork();
        if (stat[i] == 0)
        {
			if (pthread_create(&philo->thread_info[i].thread, NULL, &thread_function, &philo->thread_info[i]))
			{
				ft_error("Thread creation failed");
				exit (1);
			}
            while (1)
            	death_note(philo, i);
        }
			usleep(100);
        i++;
    }
    i = 0;
    while (i < philo->num_philo)
    {
        waitpid(stat[i], &status, 0);
		if(WIFEXITED(status))
				status = WEXITSTATUS(status);
		if (status == 0)
			i++;
        if (status == 1)
		{
			i = 0;
			while (i < philo->num_philo)
   			{
				kill(stat[i], SIGKILL);
				i++;
			}
			des_mutex(philo);
			return ;
		}
        i++;
    }
	des_mutex(philo);
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
