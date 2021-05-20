/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:59:16 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/20 06:49:34 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	checking_death(t_philo *philo)
{
	unsigned long	time;

	sem_wait(philo->args->wait);
	time = what_time();
	if (time == FAIL)
		return (FAIL);
	if (philo->is_eating == 0 && time >= philo->life_limit)
	{
		if (message(philo, "dead\n") == FAIL)
			return (FAIL);
		philo->args->death = 0;
	}
	sem_post(philo->args->wait);
	usleep(1000);
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
	while (1)
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
	while (philo->args->death && philo->args->full_meal_flag)
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

int	make_threads(t_args *args, t_philo *philo)
{
	int			i;

	i = -1;
	while (++i < args->nbr_of_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, process, (void *)&philo[i]) \
																	!= SUCCESS)
			return (FAIL);
		usleep(70);
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
	if (make_threads(&args, philo) == FAIL)
		return (FAIL);
	if (destroy(&args) == FAIL)
		return (FAIL);
	free(philo);
	return (SUCCESS);
}