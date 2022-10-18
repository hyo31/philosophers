/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/03/09 20:43:56 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_done(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&info->lock);
	if (info->dead == 1)
	{
		pthread_mutex_unlock(&info->lock);
		return (1);
	}
	while (i < info->seat)
	{
		if (info->times_eat[i] < info->max_eat || info->max_eat == -1)
		{
			pthread_mutex_unlock(&info->lock);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&info->lock);
	return (1);
}

static void	*philosopher(void *vargp)
{
	t_info			*info;
	static int		seat;
	int				new_seat;

	info = (t_info *)vargp;
	pthread_mutex_lock(&info->lock);
	seat += 1;
	new_seat = seat;
	pthread_mutex_unlock(&info->lock);
	if ((new_seat % 2) == 1)
		usleep((info->eat / 2) * 1000);
	while (!check_done(info))
	{
		lock(info, new_seat);
		eat(info, new_seat);
		unlock(info, new_seat);
		sleeping(info, new_seat);
	}
	return (NULL);
}

static void	*monitor(void *vargp)
{
	t_info		*info;
	long long	now;
	int			i;

	info = (t_info *)vargp;
	while (1 == 1)
	{
		i = 0;
		while (i < info->seat)
		{
			now = get_time_ms();
			pthread_mutex_lock(&info->lock);
			if (info->die < (now - info->last_meal[i]))
			{
				info->dead = 1;
				printf("%lli 	%i	died\n", now - info->start, i + 1);
			}
			pthread_mutex_unlock(&info->lock);
			if (check_done(info))
				return (NULL);
			i++;
		}
		usleep(900);
	}
	return (NULL);
}

static void	init_struct(t_info *info, int argc, char **argv)
{
	info->start = get_time_ms();
	info->i = 0;
	info->dead = 0;
	info->seat = ft_atoi(argv[1]);
	info->die = ft_atoi(argv[2]);
	info->eat = ft_atoi(argv[3]);
	info->sleep = ft_atoi(argv[4]);
	info->max_eat = -1;
	if (argc == 6)
		info->max_eat = ft_atoi(argv[5]);
	info->last_meal = malloc(sizeof(long long) * info->seat);
	info->times_eat = malloc(sizeof(int) * info->seat);
	info->philo = (pthread_t *)malloc(sizeof(pthread_t) * info->seat);
	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->seat);
	pthread_mutex_init(&info->lock, NULL);
	while (info->i < info->seat)
	{
		info->last_meal[info->i] = info->start;
		info->times_eat[info->i] = 0;
		pthread_mutex_init(&info->fork[info->i], NULL);
		info->i++;
	}
	pthread_mutex_init(&info->fork[info->i], NULL);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
	{
		write(2, "wrong number of arguments\n", 26);
		return (1);
	}
	init_struct(&info, argc, argv);
	pthread_create(&info.monitor, NULL, &monitor, (void *)&info);
	info.i = 0;
	while (info.i < info.seat)
	{
		pthread_create(&info.philo[info.i], NULL, &philosopher, (void *)&info);
		info.i++;
	}
	info.i = 0;
	while (info.i < info.seat)
	{
		pthread_join(info.philo[info.i], NULL);
		pthread_mutex_destroy(&info.fork[info.i]);
		info.i++;
	}
	pthread_join(info.monitor, NULL);
	pthread_mutex_destroy(&info.lock);
	return (0);
}
