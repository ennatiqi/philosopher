/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:45:00 by rennatiq          #+#    #+#             */
/*   Updated: 2023/02/26 15:02:07 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_args(char **av, int ac)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		while ((av[i][j] == ' ' || av[i][j] == '\t' || av[i][j] == '\v'
			|| av[i][j] == '\n' || av[i][j] == '\f' || av[i][j] == '\r'))
			j++;
		if (av[i][j] == '+' || av[i][j] == '-')
			j++;
		while (av[i][j])
		{
			if (!is_digit(av[i][j]))
				return (1);
			j++;
		}
	}
	return (0);
}

int	check_negativ(t_philo *philo, char **av)
{
	if (philo->num_philo < 0 || philo->time_to_die < 0 || philo->time_to_eat < 0
		|| philo->time_to_sleep < 0)
		return(1);
	if (av[5])
		if (philo->time_must_eat < 0)
			return(1);
	return (0);
}
