/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:49:05 by rennatiq          #+#    #+#             */
/*   Updated: 2023/02/25 15:13:42 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void *thread_function(void *phi)
{
	t_info	*info;
	int		id;

	info = (t_info *)phi;
	t_philo *philo;
	philo = info->philo;
	id = info->id;
	if (id % 2 != 0)
	    usleep(100);
	while (1)
	{
		ft_eat(philo,id);
		ft_sleep(philo,id);
		ft_think(philo,id);
	}
	return (NULL);
}