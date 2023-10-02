/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:54:41 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/02 04:38:43 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_data(int ac, char **av, t_data *data)
{
	data->num_philosophe = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_of_meal = ft_atoi(av[5]);
}

int	init_fork(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (printf("Function pthread_mutex_init fail\n"), 0);
	if (pthread_mutex_init(&data->died, NULL) != 0)
		return (printf("Function pthread_mutex_init fail\n"), 0);
	if (pthread_mutex_init(&data->meal_eat, NULL) != 0)
		return (printf("Function pthread_mutex_init fail\n"), 0);
	return (1);
}

int	first(t_philo *philo, t_data *data)
{
	int	i;

	if (second(philo, data) == 0)
		return (0);
	i = 0;
	while (i < data->num_philosophe - 1)
	{
		philo[i].right_fork = &philo[i + 1].left_fork;
		i++;
	}
	philo[i].right_fork = &philo[0].left_fork;
	i = 0;
	while (i < data->num_philosophe)
	{
		if (pthread_mutex_init(&philo[i].time_eat, NULL) != 0)
			return (printf("Function pthread_mutex_init fail\n"), 0);
		if (pthread_mutex_init(&philo[i].left_fork, NULL) != 0)
			return (printf("Fork %d function pthread_mutex_init fail\n", i), 0);
		i++;
	}
	return (1);
}

int	second(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophe)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].timestamp_eat = get_timestamp();
		i++;
	}
	return (1);
}

int	init_struct(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	data->time_init = get_timestamp();
	while (i < data->num_philosophe)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_thread, &philo[i])
			!= 0)
			return (printf("Philo %d function pthread_create fail\n", i), 0);
		i++;
	}
	watch_philo(philo, data);
	i = 0;
	while (i < data->num_philosophe)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (printf("Function pthread_join fail\n"),
				end_fc(philo, data), 0);
		i++;
	}
	return (1);
}
