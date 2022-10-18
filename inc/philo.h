/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/03/11 17:39:22 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_info
{
	int				i;
	long long		start;
	int				seat;
	int				eat;
	int				sleep;
	int				max_eat;
	int				die;
	pthread_t		*philo;
	pthread_t		monitor;
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock;
	long long		*last_meal;
	int				dead;
	int				*times_eat;
}	t_info;

void		lock(t_info *info, int philo);
void		eat(t_info *info, int philo);
void		unlock(t_info *info, int philo);
void		sleeping(t_info *info, int philo);
long long	get_time_ms(void);
int			ft_atoi(const char *str);
int			check_done(t_info *info);

#endif
