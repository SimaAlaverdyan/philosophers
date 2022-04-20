#include "philo.h"

void    *start(void *argv)
{
    t_philo *philo;

    philo = argv;
    if (philo->id % 2 == 0)
        usleep(philo->utils->time_to_eat * 1000);
    while (!philo->utils->finish)
    {
        // pick_fork(philo);
        // eat(philo);
        // sleep(philo);
        // think(philo);
    }
    return (0);
}

void    *show(void *argv)
{
    //monitor
    (void) argv;
    printf("show\n");
    return (0);
}

void    *show_each_must_eat(void *argv)
{
    (void) argv;
    printf("show_each\n");
    return (0);
}