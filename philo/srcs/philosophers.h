/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:10:59 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/02 01:02:31 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_data;
struct	s_philo;

typedef struct s_data
{
	long int		time_init;
	long int		num_philosophe;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		num_of_meal;
	long int		short_sleep;
	int				is_dead;
	int				num_finish_eat;
	pthread_mutex_t	print;
	pthread_mutex_t	died;
	pthread_mutex_t	meal_eat;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				ate;
	pthread_t		thread;
	pthread_mutex_t	time_eat;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	long int		timestamp_eat;
	t_data			*data;
}					t_philo;

int					start_fc(int ac, char **av);
int					check_arg(int ac, char **av);
int					check(char *str);
long int			ft_atoi(char *nptr);
void				init_data(int ac, char **av, t_data *data);
void				handle_one(t_data *data);
int					init_struct(t_philo *philo, t_data *data);
int					first(t_philo *philo, t_data *data);
int					second(t_philo *philo, t_data *data);
int					init_fork(t_data *data);
void				*philo_thread(void *arg);
int					philosophe_eat(t_philo *philo, t_data *data);
int					philosophe_eat2(t_philo *philo, t_data *data);
int					philosophe_sleep(t_philo *philo, t_data *data);
int					philosophe_think(t_philo *philo, t_data *data);
void				ft_usleep(long int usleeep, t_data *data);
void				ft_usleep2(long int usleeep);
int					ft_print(t_philo *philo, t_data *data, char *str);
long int			get_timestamp(void);
void				*ft_calloc(size_t nmemb, size_t size);
int					watch_philo(t_philo *philo, t_data *data);
int					check_death(t_philo *philo, t_data *data);
int					all_eat(t_data *data);
int					is_dead(t_data *data);
void				end_fc(t_philo *philo, t_data *data);

#endif
