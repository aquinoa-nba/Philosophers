/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:25:08 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/21 04:55:18 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

long long	ft_atoi(const char *str)
{
	int			n;
	long long	num;

	num = 0;
	n = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			n *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		num = num * 10 + *str++ - '0';
	return (num * n);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putnbr(long long n)
{
	char	nbr;

	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else if (n < 10 && n >= 0)
	{
		nbr = n + 48;
		write(1, &nbr, 1);
	}
}

int	message(t_philo *philo, char *str)
{
	unsigned long	time;

	time = what_time();
	if (time == FAIL)
		return (FAIL);
	time -= philo->args->start;
	sem_wait(philo->args->message);
	ft_putnbr(time);
	write(1, "\t", 1);
	ft_putnbr(philo->position);
	write(1, "\t", 1);
	write(1, str, ft_strlen(str));
	sem_post(philo->args->message);
	return (SUCCESS);
}

int	destroy(t_args *args)
{
	sem_unlink("forks");
	sem_unlink("message");
	sem_post(args->wait);
	sem_unlink("wait");
	sem_post(args->full);
	sem_unlink("full");
	sem_unlink("philo_is_death");
	if (sem_close(args->forks) != SUCCESS)
		return (FAIL);
	if (sem_close(args->message) != SUCCESS)
		return (FAIL);
	if (sem_close(args->wait) != SUCCESS)
		return (FAIL);
	if (sem_close(args->full) != SUCCESS)
		return (FAIL);
	if (sem_close(args->philo_is_death) != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}
