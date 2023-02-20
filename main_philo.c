/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:55:08 by rennatiq          #+#    #+#             */
/*   Updated: 2023/02/20 17:52:34 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void *thread_function(philo_t *philo)
{
    //fork -> eat -> sleep -> thinking
    eat(philo,philo->id);
    sleep(philo,philo->id);
    think(philo,philo->id);
}

int main(int ac, char **av)
{
    if (ac != 7)
        return 1;
    
    
    int num_philo;
    philo_t *philo;

    
    philo->num_philo = itoa(av[1]);
    
    philo = malloc(num_philo * sizeof(philo_t));
    int i = 0;
    while (i < num_philo)
    {
        philo->time_must_eat = itoa(av[2]);
        philo->time_to_die = itoa(av[3]);
        philo->time_to_eat = itoa(av[4]);
        philo->time_to_sleep = itoa(av[5]);
    }
    i = 0;
    while (i < num_philo)
    {
        pthread_mutex_init(&philo->fork[i], NULL);
        philo->id = i;
        i++;
    }
    i = 0;
    while (i < num_philo)
    {
        if (pthread_create(&philo->philo, NULL, thread_function, &philo ) != 0) {
            perror("Thread creation failed");
            return 1;
        }
        i++;
    }
    i = 0;
    while (i < num_philo)
    {
        if (pthread_join(&philo->philo, NULL) != 0) {
            perror("Thread creation failed");
            return 1;
        }
        i++;
    }
    i = 0;
     while (i < num_philo)
    {
        pthread_mutex_destroy(&philo->fork );
        i++;
    }    
}