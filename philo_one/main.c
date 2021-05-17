/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:59:16 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/18 02:39:38 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->forks[philo->l_fork]);
	pthread_mutex_lock(&philo->args->forks[philo->r_fork]);
	message(philo, "has taken a fork\n");
	message(philo, "has taken a fork\n");
	message(philo, "is eating\n");
	philo->is_eating = 1;
	philo->time_to_life = what_time() + philo->args->time_to_die;
	usleep(philo->args->time_to_eat * 1000);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->args->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->args->forks[philo->r_fork]);
	if (philo->args->nbr_of_eats)
	{
		philo->nbr_of_meals++;
		if (philo->nbr_of_meals == philo->args->nbr_of_eats)
		{
			message(philo, "number of meals reached\n");
			return (1);
		}
	}
	return (0);
}

void	*func2(void *p)
{
	t_philo			*philo;

	philo = (t_philo *)p;
	philo->time_to_life = what_time() + philo->args->time_to_die;
	while (1)
	{
		pthread_mutex_lock(&philo->args->wait);
		if (philo->is_eating == 0 && what_time() >= philo->time_to_life)
		{
			message(philo, "dead\n");
			philo->args->death = 0;
			pthread_mutex_unlock(&philo->args->wait);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->args->wait);
		usleep(1000);
	}
}

void	*func(void *p)
{
	t_philo			*philo;
	pthread_t		tread;

	philo = (t_philo *)p;
	pthread_create(&tread, NULL, func2, (void *)philo);
	pthread_detach(tread);
	while (philo->args->death)
	{
		if (eating(philo))
			break ;
		message(philo, "is sleeping\n");
		usleep(philo->args->time_to_sleep * 1000);
		message(philo, "is thinking\n");
	}
	return (NULL);
}

int	make_threads(t_args *args, t_philo *philo)
{
	int			i;

	i = -1;
	while (++i < args->nbr_of_philo)
	{
		pthread_create(&philo[i].tread, NULL, func, (void *)&philo[i]);
		usleep(70);
	}
	i = -1;
	while (++i < args->nbr_of_philo)
		pthread_join(philo[i].tread, NULL);
	return (0);
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
