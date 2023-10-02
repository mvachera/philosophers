/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:52:41 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/02 02:34:08 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(long int usleeep, t_data *data)
{
	long int	time;

	time = get_timestamp();
	while (get_timestamp() - time < usleeep)
	{
		if (is_dead(data) == 1)
			return ;
		usleep(10);
	}
}

int	ft_print(t_philo *philo, t_data *data, char *str)
{
	pthread_mutex_lock(&data->print);
	if (is_dead(data) == 1)
	{
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	printf("[%ld] : %d, %s\n", get_timestamp() - data->time_init, philo->id,
		str);
	pthread_mutex_unlock(&data->print);
	return (0);
}

long int	get_timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec) / 1000);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			i;
	size_t			nmemb_size;

	i = 0;
	nmemb_size = nmemb * size;
	if (nmemb_size == 0)
		return (malloc(1));
	if (nmemb == 0 || size == 0)
		return (NULL);
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = (unsigned char *)malloc(nmemb_size);
	if (!ptr)
		return (NULL);
	while (i < nmemb_size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
