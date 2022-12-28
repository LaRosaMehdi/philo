/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mla-rosa <mla-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:00:24 by mla-rosa          #+#    #+#             */
/*   Updated: 2022/12/27 18:14:37 by mla-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	*philo_monitor(void *philo)
{
	t_philo	*p;
	t_data	*data;

	p = (t_philo *)philo;
	data = (t_data *)p->data;
	while (data->is_end == false)
	{
		if (routine_the_death(p) == true || routine_option(data) == true)
			return ((void *)1);
	}
	return ((void *)0);
}

void	*philos_function(void *philo)
{
	t_philo	*p;
	t_data	*data;

	p = (t_philo *)philo;
	data = (t_data *)p->data;
	if (p->name % 2 == 0)
		usleep(1000);
	pthread_detach(p->thread);
	p->limit = timestamp(data) + data->ttdie;
	pthread_create(&p->monitor, NULL, philo_monitor, p);
	while (data->is_end == false)
	{
		routine(philo);
		if (data->is_end == true)
			return ((void *)1);
		
	}
	return ((void *)0);
}

int	philos_launcher(t_data *data)
{
	int	idx;

	idx = -1;
	while (++idx < data->nbphilos)
	{
		pthread_create(&data->philosopher[idx].thread,
			NULL, philos_function, &data->philosopher[idx]);
		usleep(100);
	}
	while (data->is_end == false)
		;
	return (0);
}
