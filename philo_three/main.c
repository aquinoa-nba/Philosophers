/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:59:16 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/21 04:55:23 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	err(char *str)
{
	printf("%s", str);
	return (FAIL);
}

int	process(t_philo *philo)
{
	pthread_t	death_thread;

	if (pthread_create(&death_thread, NULL, check_death, (void *)philo) != \
																	SUCCESS)
		return (FAIL);
	if (pthread_detach(death_thread) != SUCCESS)
		return (FAIL);
	while (1)
	{
		if (eating(philo) == FAIL)
			return (FAIL);
		if (message(philo, "is sleeping\n") == FAIL)
			return (FAIL);
		usleep(philo->args->time_to_sleep * 1000);
		if (message(philo, "is thinking\n") == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

int	make_processes(t_args *args, t_philo *philo)
{
	int			i;
	pthread_t	full;

	if (args->nbr_of_eats)
	{
		if (pthread_create(&full, NULL, check_full, (void *)args) != SUCCESS)
			return (FAIL);
		if (pthread_detach(full) != SUCCESS)
			return (FAIL);
	}
	i = -1;
	while (++i < args->nbr_of_philo)
	{
		args->pid[i] = fork();
		if (args->pid[i] < 0)
			return (FAIL);
		else if (args->pid[i] == 0)
		{
			philo->position = i + 1;
			process(philo);
			usleep(200);
		}
	}
	sem_wait(args->philo_is_death);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_args		args;
	t_philo		philo;
	int			i;

	if (ac < 5 || ac > 6)
		return (err("Error: wrong number of arguments\n"));
	else
	{
		if (init_args(&args, ac, av) == FAIL)
			return (FAIL);
	}
	init_philo(&args, &philo);
	if (make_processes(&args, &philo) == FAIL)
		return (FAIL);
	i = -1;
	while (++i < args.nbr_of_philo)
		kill(args.pid[i], SIGTERM);
	if (destroy(&args) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
