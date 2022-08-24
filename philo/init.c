/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:39:59 by sdavos            #+#    #+#             */
/*   Updated: 2022/06/16 16:40:01 by sdavos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(t_info *info, char **argv)
{
	info->number_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		info->number_of_eat = ft_atoi(argv[5]);
	pthread_mutex_init(&info->print_mutex, NULL);
	info->im_dead = 0;
	info->im_eat_many_times = 0;
	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->number_of_philo);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->number_of_philo);
	init_part_two(info);
}

void	init_part_two(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philo)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		pthread_mutex_init(&info->philo[i].check_mutex, NULL);
		info->philo[i].number = i;
		info->philo[i].is_eat = 0;
		info->philo[i].eat_count = 0;
		info->philo[i].right_hand = &info->forks[i];
		if (i == 0)
			info->philo[i].left_hand = &info->forks[info->number_of_philo - 1];
		else
			info->philo[i].left_hand = &info->forks[i - 1];
		info->philo[i].info = info;
		gettimeofday(&info->philo[i].last_eat, 0);
		i++;
	}
}

long	ft_atoi(const char *str)
{
	long	val;
	int		sign;

	val = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		val = val * 10 + *str - '0';
		str++;
	}
	return (val * sign);
}
