#include "ft_philo.h"

void	ft_putstr_fd(char *msg, int fd)
{
	if (!msg)
		return ;
	while (*msg)
		write(fd, msg++, 1);
}

void ft_error(char *msg)
{
    ft_putstr_fd("ERROR\n",2);
	ft_putstr_fd(msg,2);
}

void ft_free_pro(t_philo *philo, pthread_mutex_t *forks, t_info *thread_info)
{
	if (thread_info)
		free(thread_info);
	if (philo)
		free(philo);
	if (forks)
		free(forks);
}