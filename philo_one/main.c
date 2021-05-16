/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:59:16 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/16 18:26:33 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_1.h"

int	init_args(t_args *args, int ac, char **av)
{
	args->nbr_of_philo = ft_atoi(av[1]);
	if (args->nbr_of_philo < 2 || args->nbr_of_philo > 200)
		return (err("Error: wrong number of philosophers\n"));
	args->time_to_die = ft_atoi(av[2]);
	if (args->time_to_die < 60)
		return (err("Error: wrong time to die\n"));
	args->time_to_eat = ft_atoi(av[3]);
	if (args->time_to_eat < 60)
		return (err("Error: wrong time to eat\n"));
	args->time_to_sleep = ft_atoi(av[4]);
	if (args->time_to_sleep < 60)
		return (err("Error: wrong time to sleep\n"));
	if (ac == 6)
	{
		args->nbr_of_eats = ft_atoi(av[5]);
		if (args->nbr_of_eats < 0)
			return (err("Error: wrong number of times \
each philosopher must eat\n"));
	}
	else
		args->nbr_of_eats = 0;
	args->start = what_time();
	args->dead = 1;
	pthread_mutex_init(&args->message, NULL);
	pthread_mutex_init(&args->wait, NULL);
	return (0);
}

t_philo	*init_philo(t_args *args)
{
	int			i;
	t_philo		*philo;

	args->forks = malloc(sizeof(pthread_mutex_t) * args->nbr_of_philo);
	if (!args->forks)
		return (NULL);
	philo = malloc(sizeof(t_philo) * args->nbr_of_philo);
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < args->nbr_of_philo)
	{
		philo[i].pos = i + 1;
		philo[i].r_fork = i;
		if (i == 0)
			philo[i].l_fork = args->nbr_of_philo - 1;
		else
			philo[i].l_fork = i - 1;
		pthread_mutex_init(&args->forks[i], NULL);
		philo[i].args = args;
		philo[i].time_to_life = 0;
		philo[i].is_eating = 0;
	}
	return (philo);
}

void	*func2(void *p)
{
	t_philo			*philo;

	philo = (t_philo *)p;
	while (1)
	{
		pthread_mutex_lock(&philo->args->wait);
		if (philo->is_eating == 0 && what_time() > philo->time_to_life)
		{
			message(philo, "dead");
			philo->args->dead = 0;
			// pthread_mutex_unlock(&philo->args->wait);
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
	philo->time_to_life = what_time() + philo->args->time_to_die;
	pthread_create(&tread, NULL, func2, (void *)philo);
	pthread_detach(tread);
	while (philo->args->dead)
	{
		pthread_mutex_lock(&philo->args->forks[philo->l_fork]);
		message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->args->forks[philo->r_fork]);
		message(philo, "has taken a fork");
		message(philo, "is eating");
		philo->is_eating = 1;
		usleep(philo->args->time_to_eat * 1000);
		philo->is_eating = 0;
		philo->time_to_life = what_time() + philo->args->time_to_die;
		pthread_mutex_unlock(&philo->args->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->args->forks[philo->r_fork]);
		message(philo, "is sleeping");
		usleep(philo->args->time_to_sleep * 1000);
		message(philo, "is thinking");
	}
	return (NULL);
}

int	make_threads(t_args *args)
{
	int			i;
	t_philo		*philo;

	philo = init_philo(args);
	if (philo == NULL)
		return (1);
	i = -1;
	while (args->dead)
	{
		while (++i < args->nbr_of_philo)
		{
			pthread_create(&philo[i].tread, NULL, func, (void *)&philo[i]);
			pthread_detach(philo[i].tread);
			usleep(100);
		}
	}
	usleep(100);
	return (0);
}

int	main(int ac, char **av)
{
	t_args	args;

	if (ac < 5 || ac > 6)
		return (err("Error: wrong number of arguments\n"));
	else
	{
		if (init_args(&args, ac, av) == 1)
			return (1);
	}
	if (make_threads(&args) == 1)
		return (1);
	return (0);
}
