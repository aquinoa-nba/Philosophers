/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 20:14:44 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/21 04:55:07 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

unsigned long	what_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (FAIL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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
	args->forks = sem_open("forks", O_CREAT, 0644, args->nbr_of_philo);
	sem_unlink("message");
	args->message = sem_open("message", O_CREAT, 0644, 1);
	sem_unlink("wait");
	args->wait = sem_open("wait", O_CREAT, 0644, 1);
	sem_unlink("full");
	args->full = sem_open("full", O_CREAT, 0644, 1);
	sem_wait(args->full);
	sem_unlink("philo_is_death");
	args->philo_is_death = sem_open("philo_is_death", O_CREAT, 0644, 1);
	if (args->forks == SEM_FAILED || args->message == SEM_FAILED || \
			args->wait == SEM_FAILED || args->full == SEM_FAILED || \
									args->philo_is_death == SEM_FAILED)
		return (FAIL);
	sem_wait(args->philo_is_death);
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
	if (init_sem(args) == FAIL)
		return (FAIL);
	args->pid = malloc(sizeof(pid_t) * args->nbr_of_philo);
	args->start = what_time();
	if (args->start == FAIL)
		return (FAIL);
	return (SUCCESS);
}

t_philo	*init_philo(t_args *args, t_philo *philo)
{
	philo->position = 0;
	philo->args = args;
	philo->life_limit = 0;
	philo->is_eating = NOT_EAT;
	philo->nbr_of_meals = 0;
	return (philo);
}
