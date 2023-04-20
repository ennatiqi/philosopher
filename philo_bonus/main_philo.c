#include "ft_philo.h"

void death_note(t_philo	*philo, int id)
{
	size_t	time;
	int i = 0;

	while(i < philo->num_philo)
	{
		sem_wait(philo->koka);
		time = ft_get_time() - philo->start_time - philo->thread_info[i].last_eat_time;
		sem_post(philo->koka);
		if ((size_t)philo->time_to_die < time)
		{
			print_pro(philo, i + 1, "died");
			exit (1);
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
			exit (1);
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
            exit (1);
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
