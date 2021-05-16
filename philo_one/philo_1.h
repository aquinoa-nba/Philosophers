/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_1.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:19:33 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/16 17:53:33 by aquinoa          ###   ########.fr       */
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
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
	pthread_mutex_t	wait;
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
void			message(t_philo *philo, char *str);
unsigned long	what_time(void);
int				err(char *str);

#endif
