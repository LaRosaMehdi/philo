#include "../includes/includes.h"

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
	while (data->is_end == false)
	{
		if (routine_the_death(p) == true || routine_option(data) == true)
			return ((void *)1);
		routine(philo);
	}
	return ((void *)0);
}

int	philos_launcher(t_data *data)
{
	int	idx;

	idx = -1;
	while (++idx < data->nbphilos)
	{
		pthread_create(&data->philosopher[idx].thread, NULL, philos_function, &data->philosopher[idx]);
		usleep(100);
	}
	while (data->is_end == false);
	return (0);
}
