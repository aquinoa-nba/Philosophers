/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:19:33 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/16 22:29:07 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
	pthread_mutex_t	wait;
	pthread_mutex_t	philo_dead;
}				t_args;

typedef struct s_philo
{
	int				pos;
	int				r_fork;
	int				l_fork;
	int				is_eating;
	unsigned long	time_to_life;
	pthread_t		tread;
	t_args			*args;
}				t_philo;

long long		ft_atoi(const char *str);
size_t			ft_strlen(const char *s);
void			ft_putnbr_fd(unsigned long n, int fd);
int				init_args(t_args *args, int ac, char **av);
t_philo			*init_philo(t_args *args);
void			message(t_philo *philo, char *str);
unsigned long	what_time(void);
int				err(char *str);

#endif
