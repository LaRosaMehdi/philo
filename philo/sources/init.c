/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mla-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:00:16 by mla-rosa          #+#    #+#             */
/*   Updated: 2022/12/27 18:00:17 by mla-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

int	init_philo(t_philo *philo, t_data *data, int i)
{
	philo->data = data;
	philo->name = i + 1;
	philo->forks[0].name = philo->name - 1;
	philo->forks[1].name = philo->name;
	if (philo->name == data->nbphilos)
		philo->forks[1].name = 0;
	philo->forks[0].mutex = &data->forks[philo->forks[0].name];
	philo->forks[1].mutex = &data->forks[philo->forks[1].name];
	philo->limit = 0;
	philo->is_eating = false;
	philo->nb_lunch = 0;
	data->nb_eat[i] = &philo->nb_lunch;
	pthread_mutex_init(&philo->lunch, NULL);
	return (0);
}

t_data	*init_data_mutex(t_data *data)
{
	int	idx;

	idx = -1;
	data->is_end = false;
	pthread_mutex_init(&data->end, NULL);
	pthread_mutex_init(&data->output, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbphilos);
	if (!data->forks)
		return (NULL);
	while (++idx < data->nbphilos)
	{
		init_philo(&data->philosopher[idx], data, idx);
		pthread_mutex_init(&data->forks[idx], NULL);
	}
	return (data);
}

t_data	*init_data_tt(t_data *data, int ac, char **av)
{
	data->nbphilos = ft_atoi(av[0]);
	data->ttdie = ft_atoi(av[1]);
	data->tteat = ft_atoi(av[2]);
	data->ttsleep = ft_atoi(av[3]);
	if (data->nbphilos <= 0 || data->ttdie < 60
		|| data->tteat < 60 || data->ttsleep < 60)
		return (NULL);
	data->nb_must_eat = -1;
	if (ac == 6)
	{
		data->nb_must_eat = ft_atoi(av[4]);
		if (data->nb_must_eat <= 0)
			return (NULL);
	}
	return (data);
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data || !init_data_tt(data, ac, av))
		return (NULL);
	data->start_time = 0;
	data->start_time = timestamp(data);
	data->nb_eat = malloc(sizeof(int *) * data->nbphilos);
	data->philosopher = malloc(sizeof(t_philo) * data->nbphilos);
	if (!data->philosopher || !data->nb_eat)
		return (NULL);
	return (init_data_mutex(data));
}
