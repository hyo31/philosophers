/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/03/09 21:03:57 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	display(t_info *info, long long time, int philo, char *msg)
{
	if (check_done(info))
		return ;
	pthread_mutex_lock(&info->lock);
	if (!info->dead)
		printf("%lli	%i	%s\n", time - info->start, philo, msg);
	pthread_mutex_unlock(&info->lock);
}

void	lock(t_info *info, int philo)
{
	long long		now;

	pthread_mutex_lock(&info->fork[(philo - 1)]);
	now = get_time_ms();
	display(info, now, philo, "has taken a fork");
	if (philo == info->seat)
		pthread_mutex_lock(&info->fork[0]);
	else
		pthread_mutex_lock(&info->fork[philo]);
	now = get_time_ms();
	display(info, now, philo, "has taken a fork");
}

void	eat(t_info *info, int philo)
{
	long long		now;

	now = get_time_ms();
	display(info, now, philo, "is eating");
	pthread_mutex_lock(&info->lock);
	info->last_meal[philo - 1] = get_time_ms();
	if (info->max_eat >= 0)
		info->times_eat[philo - 1] += 1;
	pthread_mutex_unlock(&info->lock);
	while ((get_time_ms() - now) < info->eat)
		usleep(900);
}

void	unlock(t_info *info, int philo)
{
	pthread_mutex_unlock(&info->fork[(philo - 1)]);
	if (philo == info->seat)
		pthread_mutex_unlock(&info->fork[0]);
	else
		pthread_mutex_unlock(&info->fork[philo]);
}

void	sleeping(t_info *info, int philo)
{
	long long		now;

	now = get_time_ms();
	display(info, now, philo, "is sleeping");
	while ((get_time_ms() - now) < info->sleep)
		usleep(900);
	now = get_time_ms();
	display(info, now, philo, "is thinking");
}
