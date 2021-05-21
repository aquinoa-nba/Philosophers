/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:59:16 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/21 00:47:22 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	checking_death(t_philo *philo)
{
	unsigned long	time;

	if (pthread_mutex_lock(&philo->args->wait) != SUCCESS)
		return (FAIL);
	time = what_time();
	if (time == FAIL)
		return (FAIL);
	if (philo->is_eating == NOT_EAT && time >= philo->life_limit)
	{
		if (message(philo, "dead\n") == FAIL)
			return (FAIL);
		philo->args->death = DEAD;
	}
	if (pthread_mutex_unlock(&philo->args->wait) != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}

void	*check_death(void *p)
{
	t_philo			*philo;
	int				death_checker;
	unsigned long	time;

	philo = (t_philo *)p;
	time = what_time();
	if (time == FAIL)
		return ((void *)FAIL);
	philo->life_limit = time + philo->args->time_to_die;
	while (philo->args->death == ALIVE && philo->args->full_meal_flag)
	{
		death_checker = checking_death(philo);
		if (death_checker == FAIL)
			return ((void *)FAIL);
	}
	return ((void *)SUCCESS);
}

void	*process(void *p)
{
	t_philo			*philo;
	pthread_t		death_thread;

	philo = (t_philo *)p;
	if (pthread_create(&death_thread, NULL, check_death, (void *)philo) != \
																	SUCCESS)
		return ((void *)FAIL);
	if (pthread_detach(death_thread) != SUCCESS)
		return ((void *)FAIL);
	while (philo->args->death == ALIVE && philo->args->full_meal_flag)
	{
		if (eating(philo) == FAIL)
			return ((void *)FAIL);
		if (message(philo, "is sleeping\n") == FAIL)
			return ((void *)FAIL);
		usleep(philo->args->time_to_sleep * 1000);
		if (message(philo, "is thinking\n") == FAIL)
			return ((void *)FAIL);
	}
	return ((void *)SUCCESS);
}

int	make_processes(t_args *args, t_philo *philo)
{
	int			i;

	i = -1;
	while (++i < args->nbr_of_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, process, (void *)&philo[i]) \
																	!= SUCCESS)
			return (FAIL);
		usleep(200);
	}
	i = -1;
	while (++i < args->nbr_of_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != SUCCESS)
			return (FAIL);
	}
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_args		args;
	t_philo		*philo;

	if (ac < 5 || ac > 6)
		return (err("Error: wrong number of arguments\n"));
	else
	{
		if (init_args(&args, ac, av) == FAIL)
			return (FAIL);
	}
	philo = init_philo(&args);
	if (philo == NULL)
		return (FAIL);
	if (make_processes(&args, philo) == FAIL)
		return (FAIL);
	if (destroy(&args) == FAIL)
		return (FAIL);
	free(philo);
	return (SUCCESS);
}
