/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:10:05 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/02 02:45:19 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep2(long int usleeep)
{
	long int	time;

	time = get_timestamp();
	while (get_timestamp() - time < usleeep)
		usleep(10);
}

int	start_fc(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (printf("Error\nIncorrect number of arguments\n"), 0);
	if (check_arg(ac, av) == 0)
		return (printf("Error\nArguments are incorrects\n"), 0);
	return (1);
}

void	end_fc(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophe)
	{
		pthread_mutex_destroy(&philo[i].time_eat);
		pthread_mutex_destroy(&philo[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(&data->meal_eat);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->died);
	free(philo);
}

int	main(int ac, char **av)
{
	t_philo				*philo;
	static t_data		data = {0};

	if (start_fc(ac, av) == 0)
		return (0);
	init_data(ac, av, &data);
	if (data.num_philosophe == 1)
	{
		data.time_init = get_timestamp();
		return (handle_one(&data), 0);
	}
	philo = ft_calloc(sizeof(t_philo), data.num_philosophe);
	if (philo == NULL)
		return (printf("Function malloc fail for philo\n"), 0);
	if (init_fork(&data) == 0)
		return (free(philo), 0);
	if (first(philo, &data) == 0)
		return (end_fc(philo, &data), 0);
	if (init_struct(philo, &data) == 0)
		return (end_fc(philo, &data), 0);
	end_fc(philo, &data);
}
