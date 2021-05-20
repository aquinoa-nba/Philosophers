/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 20:14:44 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/20 06:49:32 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

int	init_sem(t_args *args)
{
	sem_unlink("forks");
	sem_unlink("message");
	sem_unlink("wait");
	args->forks = sem_open("forks", O_CREAT, 0644, args->nbr_of_philo);
	args->message = sem_open("message", O_CREAT, 0644, 1);
	args->wait = sem_open("wait", O_CREAT, 0644, 1);
	if (args->forks == SEM_FAILED || args->message == SEM_FAILED || \
													args->wait == SEM_FAILED)
		return (FAIL);
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
	args->full_meal_counter = 0;
	args->full_meal_flag = 1;
	if (init_sem(args) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

t_philo	*init_philo(t_args *args)
{
	t_philo		*philo;
	int			i;

	philo = malloc(sizeof(t_philo) * args->nbr_of_philo);
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < args->nbr_of_philo)
	{
		philo[i].position = i + 1;
		philo[i].args = args;
		philo[i].life_limit = 0;
		philo[i].is_eating = 0;
		philo[i].nbr_of_meals = 0;
	}
	return (philo);
}
