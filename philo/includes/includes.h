#ifndef INCLUDES_H
# define INCLUDES_H

# include <stdio.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_fork
{
	pthread_mutex_t	*mutex;
	int				name;
}	t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	t_fork			forks[2];
	int				name;
	long			limit;
	bool			is_eating;
	int				nb_lunch;
	pthread_mutex_t	lunch;
	void			*data;

}	t_philo;

typedef struct s_data
{
	long			start_time;
	int				nbphilos;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				nb_must_eat;
	int				**nb_eat;
	t_philo			*philosopher;
	pthread_mutex_t	*forks;
	pthread_mutex_t	output;
	pthread_mutex_t	end;
	bool			is_end;
}	t_data;

int		main(int ac, char **av);

t_data	*init_data(int ac, char **av);
t_data	*init_data_mutex(t_data *data);
int		init_philo(t_philo *philo, t_data *data, int i);

int		philos_launcher(t_data *data);
void	*philos_function(void *philo);
int		philos_melody(void *data);

void	routine(t_philo *philo);
bool	routine_option(t_data *data);
bool	routine_the_death(t_philo *philo);
void	routine_output(t_philo *philo, char *routine, bool option);

int		ft_atoi(char *str);
int		ft_str_is_digits(char *str);
int		error(t_data *data);
int		end(t_data *data);
long	timestamp(t_data *data);

#endif