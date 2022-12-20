#include "../includes/includes.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac == 5 || ac == 6)
	{
		data = init_data(ac, av + 1);
		if (data == NULL)
			return (error(data));
		return (philos_launcher(data));
	}
	return (error(data));
}
