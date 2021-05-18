/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 20:14:44 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/18 19:07:29 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validation(t_args *args)
{
	if (args->nbr_of_philo < 2 || args->nbr_of_philo > 200)
		return (err("Error: wrong number of philosophers\n"));
	if (args->time_to_die < 60)
		return (err("Error: wrong time to die\n"));
	if (args->time_to_eat < 60)
		return (err("Error: wrong time to eat\n"));
	if (args->time_to_sleep < 60)
		return (err("Error: wrong time to sleep\n"));
	if (args->nbr_of_eats < 0)
		return (err("Error: wrong number of times \
each philosopher must eat\n"));
	return (SUCCESS);
}

int	init_args(t_args *args, int ac, char **av)
{
	args->nbr_of_philo = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		args->nbr_of_eats = ft_atoi(av[5]);
	else
		args->nbr_of_eats = 0;
	if (validation(args) == FAIL)
		return (FAIL);
	args->start = what_time();
	if (args->start == FAIL)
		return (FAIL);
	args->death = 1;
	if (pthread_mutex_init(&args->message, NULL) != SUCCESS)
		return (FAIL);
	if (pthread_mutex_init(&args->wait, NULL) != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}

t_philo	*init_philo(t_args *args)
{
	t_philo		*philo;
	int			i;

	args->forks = malloc(sizeof(pthread_mutex_t) * args->nbr_of_philo);
	philo = malloc(sizeof(t_philo) * args->nbr_of_philo);
	if (!args->forks || !philo)
		return (NULL);
	i = -1;
	while (++i < args->nbr_of_philo)
	{
		philo[i].position = i + 1;
		philo[i].r_fork = i;
		if (i == 0)
			philo[i].l_fork = args->nbr_of_philo - 1;
		else
			philo[i].l_fork = i - 1;
		if (pthread_mutex_init(&args->forks[i], NULL) != SUCCESS)
			return (NULL);
		philo[i].args = args;
		philo[i].life_limit = 0;
		philo[i].is_eating = 0;
		philo[i].nbr_of_meals = 0;
	}
	return (philo);
}
