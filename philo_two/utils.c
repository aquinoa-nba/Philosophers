/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:25:08 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/21 00:42:15 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	err(char *str)
{
	printf("%s", str);
	return (FAIL);
}

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

unsigned long	what_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (FAIL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	message(t_philo *philo, char *str)
{
	unsigned long	time;

	sem_wait(philo->args->message);
	if (philo->args->death && philo->args->full_meal_flag)
	{
		time = what_time();
		if (time == FAIL)
			return (FAIL);
		time -= philo->args->start;
		printf("%lu\t%d\t%s", time, philo->position, str);
	}
	sem_post(philo->args->message);
	return (SUCCESS);
}

int	destroy(t_args *args)
{
	sem_unlink("forks");
	if (sem_close(args->forks) != SUCCESS)
		return (FAIL);
	sem_unlink("message");
	if (sem_close(args->message) != SUCCESS)
		return (FAIL);
	sem_unlink("wait");
	if (sem_close(args->wait) != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}
