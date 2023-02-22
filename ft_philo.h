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
#include <time.h>



typedef struct ft_philo
{
    pthread_t       philo[200];
    pthread_mutex_t fork[200];
    int             id;

    int             last_eat_date;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             time_must_eat;

}                    philo_t;
void eat(philo_t *philo, int id);
int think(philo_t *philo, int id);
void slep(philo_t *philo, int id);
int	ft_atoi(char *n);


#endif