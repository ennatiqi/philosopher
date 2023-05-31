/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:45:00 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/29 09:23:50 by rennatiq         ###   ########.fr       */
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
	if (philo->time_to_die < 0 || philo->time_to_eat < 0
		|| philo->time_to_sleep < 0)
		return (1);
	if (av[5])
		if (philo->time_must_eat < 0)
			return (1);
	return (0);
}

t_philo	*first_step(char **av, int ac)
{
	t_philo	*philo;

	if (check_args(av, ac))
	{
		ft_error("your args mast be integers");
		return (NULL);
	}
	philo = init_args(av);
	if (av[5])
		if (philo->time_must_eat == 0)
			return (NULL);
	if (check_negativ(philo, av))
	{
		if (philo)
			free(philo);
		ft_error("your args mast be positive");
		return (NULL);
	}
	if (philo->num_philo <= 0)
	{
		if (philo)
			free(philo);
		ft_error("your num_philo mast be more than 0");
		return (NULL);
	}
	thread_info_init_fork(philo);
	return (philo);
}
