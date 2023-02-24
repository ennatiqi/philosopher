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
	
	unsigned long       last_eat_time;



	struct s_philo		*philo;
	pthread_t			thread;
}						t_info;

typedef struct			s_philo
{
    int					num_philo;
	unsigned long       start_time;
	unsigned long       time_to_sleep;
    unsigned long       time_to_eat;
    unsigned long       time_to_die;
    unsigned long       time_must_eat;

	int					death_note;
	pthread_mutex_t		*forks;
	t_info	        	*thread_info;
}						t_philo;

void ft_eat(t_philo *philo, int id);
int ft_think(t_philo *philo, int id);
void ft_sleep(t_philo *philo, int id);
unsigned long ft_get_time(void);

int	ft_atoi(char *n);
void died(t_philo *philo);


#endif