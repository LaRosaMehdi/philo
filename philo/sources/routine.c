#include "../includes/includes.h"

void routine_output(t_philo *philo, char *routine, bool option)
{
	t_data *data;
	
	data = (t_data*)philo->data;
	pthread_mutex_lock(&data->end);
	if (data->is_end == true)
		return ((void)pthread_mutex_unlock(&data->end));
	pthread_mutex_unlock(&data->end);
	pthread_mutex_lock(&data->output);
	if (option == false)
		printf("%ld\t%d %s\n", timestamp(data), philo->name, routine);
	else
		printf("%ld\t%s\n", timestamp(data), routine);
	pthread_mutex_unlock(&data->output);
}

bool routine_the_death(t_philo *philo)
{
	t_data *data = NULL;

	data = (t_data*)philo->data;
	if (philo->is_eating == false && philo->limit > 0 && timestamp(data) > philo->limit)
	{
		routine_output(philo, "died", false);
		pthread_mutex_lock(&data->end);
		data->is_end = true;
		pthread_mutex_unlock(&data->end);
		return (true);
	}
	return (false);
}

bool routine_option(t_data *data)
{
	int i;

	if (data->nb_must_eat == -1)
		return (false);
	i = -1;
	while (++i < data->nbphilos)
	{
		if (data->philosopher[i].nb_lunch < data->nb_must_eat) 
			return (false);
	}
	routine_output(&data->philosopher[0], "must it counter reached", true);
	pthread_mutex_lock(&data->end);
	data->is_end = true;
	pthread_mutex_unlock(&data->end);
	return (true);
}

void routine_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->forks[0].mutex);
	routine_output(philo, "has taken a fork", false);
	pthread_mutex_lock(philo->forks[1].mutex);
	routine_output(philo, "has taken a fork", false);
	philo->is_eating = true;
	routine_output(philo, "is eating", false);
	usleep(data->tteat * 1000);
	philo->limit += data->ttdie;
	pthread_mutex_unlock(philo->forks[0].mutex);
	pthread_mutex_unlock(philo->forks[1].mutex);
	philo->is_eating = false;
}

void routine(t_philo *philo)
{
	t_data *data;
	
	data = (t_data*)philo->data;
	routine_eat(data, philo);
	if (data->nb_must_eat > -1)
	{
		pthread_mutex_lock(&philo->lunch);
		philo->nb_lunch++;
		pthread_mutex_unlock(&philo->lunch);
	}
	routine_output(philo, "is sleeping", false);
	usleep(data->ttsleep * 1000);
	routine_output(philo, "is thinking", false);
}
		