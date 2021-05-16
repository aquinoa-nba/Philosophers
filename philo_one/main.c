/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:59:16 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/16 22:50:08 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
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
			philo->args->dead = 0;
			pthread_mutex_unlock(&philo->args->philo_dead);
			usleep(100);
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
	while (philo->args->dead)
	{
		pthread_mutex_lock(&philo->args->forks[philo->l_fork]);
		message(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->args->forks[philo->r_fork]);
		message(philo, "has taken a fork\n");
		message(philo, "is eating\n");
		philo->is_eating = 1;
		usleep(philo->args->time_to_eat * 1000);
		philo->time_to_life = what_time() + philo->args->time_to_die;
		philo->is_eating = 0;
		pthread_mutex_unlock(&philo->args->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->args->forks[philo->r_fork]);
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
		pthread_detach(philo[i].tread);
		usleep(100);
	}
	pthread_mutex_lock(&args->philo_dead);
	usleep(100);
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
		if (init_args(&args, ac, av) == 1)
			return (1);
	}
	philo = init_philo(&args);
	if (philo == NULL)
		return (1);
	if (make_threads(&args, philo) == 1)
		return (1);
	free(philo);
	return (0);
}
