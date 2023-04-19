
#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
#include <semaphore.h>
#include <signal.h>



struct	s_philo;

typedef struct s_info
{
	int				id;
	size_t	last_eat_time;
	int				eat_times;
	struct s_philo	*philo;
	pthread_t		thread;
}					t_info;

typedef struct s_philo
{
	int				num_philo;
	size_t	start_time;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				time_must_eat;
	int				death_note;
	sem_t			*forks;
	sem_t	koka;
	sem_t	print;

	t_info			*thread_info;
}					t_philo;

void			ft_eat(t_philo *philo, int id);
int				ft_think(t_philo *philo, int id);
void			ft_sleep(t_philo *philo, int id);
t_philo			*init_args(char **av);
void			thread_info_init_fork(t_philo *philo);
size_t			ft_get_time(void);
int				check_negativ(t_philo *philo, char **av);
void			*thread_function(void *phi);
int				ft_atoi(char *n);
void			des_mutex(t_philo *philo);
int				check_args(char **av, int ac);
int				test_death(t_philo *philo, int id);
void			join_threads(t_philo	*philo);
void			ft_error(char *msg);
void			ft_free_pro(t_philo *philo, sem_t	*forks,
					t_info	*thread_info);
void			ft_putstr_fd(char *msg, int fd);
t_philo			*first_step(char **av, int ac);
void			nano_sleep(int time_to_sleep);
void 			print_pro(t_philo *philo,int id, char *str);
void creat_processes(t_philo *philo);

#endif