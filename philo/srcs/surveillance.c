/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surveillance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:06:05 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/02 00:53:54 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	watch_philo(t_philo *philo, t_data *data)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < data->num_philosophe)
		{
			if (check_death(&philo[i], data) == 1)
				return (1);
			if (data->num_of_meal != 0 && all_eat(data) == 1)
				return (1);
			i++;
		}
		usleep(500);
	}
	return (0);
}

int	all_eat(t_data *data)
{
	pthread_mutex_lock(&data->meal_eat);
	if (data->num_finish_eat >= data->num_philosophe)
	{
		pthread_mutex_unlock(&data->meal_eat);
		pthread_mutex_lock(&data->died);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->died);
		return (1);
	}
	pthread_mutex_unlock(&data->meal_eat);
	return (0);
}

int	check_death(t_philo *philo, t_data *data)
{
	long int	time_elapsed;
	long int	current_time;

	pthread_mutex_lock(&philo->time_eat);
	current_time = get_timestamp();
	time_elapsed = current_time - philo->timestamp_eat;
	pthread_mutex_unlock(&philo->time_eat);
	if (time_elapsed >= data->time_to_die)
	{
		pthread_mutex_lock(&data->died);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->died);
		pthread_mutex_lock(&data->print);
		printf("[%ld] : %d, is died!\n", get_timestamp()
			- data->time_init, philo->id);
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	return (0);
}

int	is_dead(t_data *data)
{
	pthread_mutex_lock(&data->died);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->died);
		return (1);
	}
	pthread_mutex_unlock(&data->died);
	return (0);
}

void	handle_one(t_data *data)
{
	printf("[%ld] : 1, has taken a fork!\n", get_timestamp() - data->time_init);
	ft_usleep2(data->time_to_die);
	printf("[%ld] : 1, died!\n", get_timestamp() - data->time_init);
}
