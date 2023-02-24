/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:44:28 by rennatiq          #+#    #+#             */
/*   Updated: 2023/02/21 17:15:10 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
# include <sys/time.h>
 
struct s_philo;

typedef	struct			s_info
{
	int					id;
	int					num_philo;
	unsigned long       last_est_time;



	struct s_philo		*philo;
	pthread_t			thread;
}						t_info;

typedef struct			s_philo
{
    
	unsigned long       start_time;
	unsigned long                 time_to_sleep;
    unsigned long                 time_to_eat;
    unsigned long                 time_to_die;
    unsigned long                 time_must_eat;
	pthread_mutex_t		*forks;
	t_info	        	*thread_info;
}						t_philo;

void ft_eat(t_info *philo, int id);
int ft_think(t_info *philo, int id);
void ft_sleep(t_info *philo, int id);
unsigned long ft_get_time(void);

int	ft_atoi(char *n);


#endif