/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:59:16 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/15 22:08:22 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_1.h"

int	err(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

unsigned long	what_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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
	pthread_mutex_init(&args->message, NULL);
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
		philo[i].args = args;
		philo[i].pos = i + 1;
		philo[i].r_fork = i;
		if (i == 0)
			philo[i].l_fork = args->nbr_of_philo - 1;
		else
			philo[i].l_fork = i - 1;
		pthread_mutex_init(&args->forks[i], NULL);
	}
	return (philo);
}

void	message(t_philo *philo, char *str)
{
	unsigned long	time;

	time = what_time() - philo->args->start;
	pthread_mutex_lock(&philo->args->message);
	printf("%lu\t%d\t%s\n", time, philo->pos, str);
	pthread_mutex_unlock(&philo->args->message);
}

void	*func(void *p)
{
	t_philo		*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(&philo->args->forks[philo->l_fork]);
	message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->args->forks[philo->r_fork]);
	message(philo, "has taken a fork");
	message(philo, "is eating");
	usleep(philo->args->time_to_eat);
	pthread_mutex_unlock(&philo->args->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->args->forks[philo->r_fork]);
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
	while (++i < args->nbr_of_philo)
	{
		pthread_create(&philo[i].tread, NULL, func, (void *)&philo[i]);
		usleep(100000);
	}
	i = -1;
	while (++i < args->nbr_of_philo)
	{
		pthread_join(philo[i].tread, NULL);
	}
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
