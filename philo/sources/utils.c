#include "../includes/includes.h"

long	timestamp(t_data *data)
{
	struct timeval	tv;
	long			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (timestamp - data->start_time);
}

int	error(t_data *data)
{
	if (data != NULL)
	{
		if (data->philosopher != NULL)
			free(data->philosopher);
		free(data);
	}
	printf("Error\n");
	return (1);
}

int	ft_str_is_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	res;

	res = 0;
	if (ft_str_is_digits(str) == -1)
		return (0);
	while (*str == ' ' && (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 - *str + '0';
		str++;
	}
	return (-res);
}
