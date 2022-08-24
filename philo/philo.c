/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:43:57 by sdavos            #+#    #+#             */
/*   Updated: 2022/06/16 16:43:59 by sdavos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	print_message(philo, "is thinking");
}

void	sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->info->time_to_sleep);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->check_mutex);
	gettimeofday(&philo->last_eat, NULL);
	pthread_mutex_unlock(&philo->check_mutex);
	print_message(philo, "is eating");
	ft_usleep(philo->info->time_to_eat);
	philo->eat_count += 1;
	if (philo->info->number_of_eat != 0
		&& (philo->eat_count == philo->info->number_of_eat))
		philo->info->im_eat_many_times += 1;
	pthread_mutex_unlock(philo->right_hand);
	pthread_mutex_unlock(philo->left_hand);
}

void	pickup_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_hand);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_hand);
	print_message(philo, "has taken a fork");
}

void	*philo(void *argv)
{
	t_philo	*philo;

	philo = argv;
	gettimeofday(&philo->create_time, NULL);
	if (philo->number % 2 != 0)
		usleep(200);
	while (1)
	{
		pickup_fork(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
