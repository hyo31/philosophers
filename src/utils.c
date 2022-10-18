/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/03/11 17:39:06 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	skip_space(const char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	rtn;
	int	t;

	i = skip_space(str, 0);
	n = 1;
	rtn = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	t = i;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		rtn = rtn * 10;
		rtn = rtn + (str[i] - '0');
		i++;
		if (i >= 26)
			return ((t - 1) * n);
	}
	return (rtn * n);
}

long long	get_time_ms(void)
{
	long long		ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	return (ms);
}
