#include "philo.h"

void	parse_args(t_utils *utils, int argc, char **argv)
{
	utils->number_of_philosophers = ft_atoi(argv[1]);
	utils->time_to_die = ft_atoi(argv[2]);
	utils->time_to_eat = ft_atoi(argv[3]);
	utils->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		utils->number_of_must_eat = ft_atoi(argv[5]);
}

int	init(t_utils *util, int argc, char **argv)
{
	parse_args(util, argc, argv);
	//check
	printf("here1");
	return (1);
}
