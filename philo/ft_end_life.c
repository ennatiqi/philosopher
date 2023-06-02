/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:35:40 by rennatiq          #+#    #+#             */
/*   Updated: 2023/06/01 18:20:14 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	ft_putstr_fd(char *msg, int fd)
{
	if (!msg)
		return ;
	while (*msg)
		write(fd, msg++, 1);
}

void	ft_free_pro(t_philo *philo, pthread_mutex_t *forks, t_info *thread_info)
{	
	if (thread_info)
		free(thread_info);
	if (philo)
		free(philo);
	if (forks)
		free(forks);
}
