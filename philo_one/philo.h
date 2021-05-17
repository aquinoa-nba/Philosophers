/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:19:33 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/18 02:39:27 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

# define SUCCESS 0
# define FAIL 1

typedef struct s_args
{
	int					nbr_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_of_eats;
	unsigned long		start;
	int					death;
	pthread_mutex_t		*forks;
	pthread_mutex_t		message;
	pthread_mutex_t		wait;
}				t_args;

typedef struct s_philo
{
	int					pos;
	int					r_fork;
	int					l_fork;
	int					is_eating;
	int					nbr_of_meals;
	unsigned long		time_to_life;
	pthread_t			tread;
	t_args				*args;
}				t_philo;

long long		ft_atoi(const char *str);
int				init_args(t_args *args, int ac, char **av);
t_philo			*init_philo(t_args *args);
unsigned long	what_time(void);
int				eating(t_philo *philo);
void			message(t_philo *philo, char *str);
int				destroy(t_args *args);
int				err(char *str);

#endif
