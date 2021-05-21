/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:19:33 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/21 04:54:03 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <stdio.h>
# include <signal.h>

# define SUCCESS 	0
# define FAIL 		1
# define BREAK 		2
# define EAT 		1
# define NOT_EAT 	0

typedef struct s_args
{
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_eats;
	unsigned long	start;
	sem_t			*forks;
	sem_t			*message;
	sem_t			*wait;
	sem_t			*full;
	sem_t			*philo_is_death;
	pid_t			*pid;
}				t_args;

typedef struct s_philo
{
	int				position;
	int				is_eating;
	int				nbr_of_meals;
	unsigned long	life_limit;
	t_args			*args;
}				t_philo;

long long		ft_atoi(const char *str);
int				init_args(t_args *args, int ac, char **av);
t_philo			*init_philo(t_args *args, t_philo *philo);
void			*check_death(void *p);
void			*check_full(void *a);
unsigned long	what_time(void);
int				eating(t_philo *philo);
int				message(t_philo *philo, char *str);
int				destroy(t_args *args);
int				err(char *str);

#endif
