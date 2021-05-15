/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_1.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:19:33 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/15 21:06:59 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_1_H
# define PHILO_1_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# include <stdio.h>

typedef struct s_args
{
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_eats;
	unsigned long	start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
}				t_args;

typedef struct s_philo
{
	int				pos;
	int				r_fork;
	int				l_fork;
	pthread_t		tread;
	t_args			*args;
	// t_philo			*philo;
	// unsigned long	start;
}				t_philo;


long long	ft_atoi(const char *str);
size_t		ft_strlen(const char *s);

#endif
