/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 04:53:02 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/21 04:55:36 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	checking_death(t_philo *philo)
{
	unsigned long	time;

	sem_wait(philo->args->wait);
	time = what_time();
	if (time == FAIL)
		return (FAIL);
	if (philo->is_eating == NOT_EAT && time >= philo->life_limit)
	{
		if (message(philo, "dead\n") == FAIL)
			return (FAIL);
		sem_wait(philo->args->message);
		return (BREAK);
	}
	sem_post(philo->args->wait);
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
		if (death_checker == BREAK)
			break ;
		else if (death_checker == FAIL)
			return ((void *)FAIL);
	}
	sem_post(philo->args->philo_is_death);
	return ((void *)SUCCESS);
}

void	*check_full(void *a)
{
	int		i;
	t_args	*args;

	args = (t_args *)a;
	i = 0;
	while (i != args->nbr_of_philo)
	{
		sem_wait(args->full);
		i++;
	}
	sem_wait(args->message);
	sem_post(args->philo_is_death);
	return ((void *)SUCCESS);
}
