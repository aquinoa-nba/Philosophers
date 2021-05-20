/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 18:28:23 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/20 06:49:26 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	finish_eating(t_philo *philo)
{
	philo->is_eating = 0;
	sem_post(philo->args->forks);
	sem_post(philo->args->forks);
	return (SUCCESS);
}

int	start_eating(t_philo *philo)
{
	unsigned long	time;

	sem_wait(philo->args->forks);
	if (message(philo, "has taken a fork\n") == FAIL)
		return (FAIL);
	sem_wait(philo->args->forks);
	if (message(philo, "has taken a fork\n") == FAIL)
		return (FAIL);
	if (message(philo, "is eating\n") == FAIL)
		return (FAIL);
	philo->is_eating = 1;
	time = what_time();
	if (time == FAIL)
		return (FAIL);
	philo->life_limit = time + philo->args->time_to_die;
	return (SUCCESS);
}

int	eating(t_philo *philo)
{
	if (start_eating(philo) == FAIL)
		return (FAIL);
	usleep(philo->args->time_to_eat * 1000);
	if (finish_eating(philo) == FAIL)
		return (FAIL);
	if (philo->args->nbr_of_eats)
	{
		philo->nbr_of_meals++;
		if (philo->nbr_of_meals >= philo->args->nbr_of_eats)
		{
			philo->args->full_meal_counter++;
			if (philo->args->full_meal_counter >= philo->args->nbr_of_philo)
				philo->args->full_meal_flag = 0;
		}
	}
	return (SUCCESS);
}
