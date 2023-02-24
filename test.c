
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# define RED "\033[1;31m"
# define RESET "\033[0m"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define DIED "is died"
# define FORK "has taken a fork"
# define THINKING "is thinking"

typedef struct s_args
{
	unsigned long	lunch_time;
	int				philo_nb;
	int				ate_max;
	unsigned long	death_t;
	unsigned long	meal_t;
	unsigned long	bed_t;
	int				should_eat;
	int				meals_limit;
}	t_args;

typedef struct	s_philo
{
	t_args			*data;
	int				id;
	int				meals_count;
	int				some_one_died;
	unsigned long	last_meal_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}					t_philo;

int	ft_create_threads(pthread_t *thread, void *ft_routine, t_philo *philo)
{
	int	i;

	i = -1;
	thread = (pthread_t *)malloc(philo->data->philo_nb * sizeof(pthread_t));
	while (++i < philo->data->philo_nb)
	{
		pthread_create(&thread[i], NULL, ft_routine, philo + i);
		usleep(100);
	}
	return (1);
}
void *ft_routine(void *ptr)
{
    t_philo	*philo;
	int		id;

	philo = (t_philo *)ptr;
	id = philo->id;
	printf("%d  ",id);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_args		*args;
	t_philo		*philo;
	pthread_t	*thread;

	if (ac == 5 || ac == 6)
	{
		args = (t_args *)malloc(sizeof(t_args));
		philo = (t_philo *)malloc(5 * sizeof(t_philo));
		
	ft_create_threads(thread, ft_routine, philo);
    }
	
}