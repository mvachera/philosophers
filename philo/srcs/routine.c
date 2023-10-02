/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:21:55 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/02 02:39:16 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_thread(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 7, philo->data);
	while (1)
	{
		if (philo->data->num_philosophe % 2 == 1)
			ft_usleep(philo->data->time_to_eat / 7, philo->data);
		if (philo->id % 2 == 1)
		{
			if (philosophe_eat(philo, philo->data) == 0)
				break ;
		}
		else if (philo->id % 2 == 0)
		{
			if (philosophe_eat2(philo, philo->data) == 0)
				break ;
		}
		if (philosophe_sleep(philo, philo->data) == 0)
			break ;
		if (philosophe_think(philo, philo->data) == 0)
			break ;
	}
	return (NULL);
}

int	philosophe_eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->left_fork);
	if (ft_print(philo, data, "has taken a fork."))
		return (pthread_mutex_unlock(&philo->left_fork), 0);
	pthread_mutex_lock(philo->right_fork);
	if (ft_print(philo, data, "has taken a fork."))
		return (pthread_mutex_unlock(&philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), 0);
	pthread_mutex_lock(&philo->time_eat);
	philo->timestamp_eat = get_timestamp();
	pthread_mutex_unlock(&philo->time_eat);
	philo->ate++;
	if (philo->ate == data->num_of_meal)
	{
		pthread_mutex_lock(&data->meal_eat);
		data->num_finish_eat++;
		pthread_mutex_unlock(&data->meal_eat);
	}
	if (ft_print(philo, data, "is eating.") == 1)
		return (pthread_mutex_unlock(&philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), 0);
	ft_usleep(data->time_to_eat, data);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

int	philosophe_eat2(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->right_fork);
	if (ft_print(philo, data, "has taken a fork."))
		return (pthread_mutex_unlock(philo->right_fork), 0);
	pthread_mutex_lock(&philo->left_fork);
	if (ft_print(philo, data, "has taken a fork."))
		return (pthread_mutex_unlock(philo->right_fork),
			pthread_mutex_unlock(&philo->left_fork), 0);
	pthread_mutex_lock(&philo->time_eat);
	philo->timestamp_eat = get_timestamp();
	pthread_mutex_unlock(&philo->time_eat);
	philo->ate++;
	if (philo->ate == data->num_of_meal)
	{
		pthread_mutex_lock(&data->meal_eat);
		data->num_finish_eat++;
		pthread_mutex_unlock(&data->meal_eat);
	}
	if (ft_print(philo, data, "is eating.") == 1)
		return (pthread_mutex_unlock(philo->right_fork),
			pthread_mutex_unlock(&philo->left_fork), 0);
	ft_usleep(data->time_to_eat, data);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	return (1);
}

int	philosophe_sleep(t_philo *philo, t_data *data)
{
	if (ft_print(philo, data, "is sleeping.") == 1)
		return (0);
	ft_usleep(data->time_to_sleep, data);
	return (1);
}

int	philosophe_think(t_philo *philo, t_data *data)
{
	if (ft_print(philo, data, "is thinking.") == 1)
		return (0);
	return (1);
}
