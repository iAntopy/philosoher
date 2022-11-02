/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:13:18 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/01 22:19:36 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	plato_clear(t_plato *pt, int ret_value)
{
	if (!pt)
		return (ret_value);
	usleep(50000);
	printf("plato clear : entered \n");
	
	if (pt->death_occured)
		sem_post(pt->death_occured);
	printf("plato clear : philos freed SUCCESSFULLY \n");

	pt->bloat_counter = INT_MAX;
	if (pt->philos_all_full)
		sem_post(pt->philos_all_full);
	if (pt->bloat_counter_th)
		pthread_join(pt->bloat_counter_th, NULL);
	
	sem_unlink(FORK_SEM_PATH);
	sem_unlink(DEATH_SEM_PATH);
	sem_unlink(BLOATED_SEM_PATH);
	sem_unlink(PRINT_SEM_PATH);
	sem_close(pt->forks);
	sem_close(pt->death_occured);
	sem_close(pt->philos_all_full);
	sem_close(pt->print_lock);


	return (ret_value);
}

int	philo_init(t_plato *pt, t_philo *ph, int i)
{
	printf("init philos : pt, ph : %p, %p\n", pt, ph);
//	printf("malloc init philos : calloc SUCCESSFULL\n");
	ph->nb_id = i;
	ph->__id_len = ft_putnbr_buff(ph->id, i + 1);
	ph->delays = pt->delays;
	ph->log_msg = pt->log_msg;
	ph->log_msg_len = (const int *)pt->log_msg_len;
	ph->death_occured = pt->death_occured;
	ph->print_lock = pt->print_lock;
	ph->forks = pt->forks;
	ph->philos_all_full = pt->philos_all_full;
	printf("init philos : return SUCCESSFULL\n");
	return (0);
}

int	plato_init_semaphores(t_plato *pt)
{
	pt->forks = sem_open("./forks.sem", O_CREAT, 0644, pt->np);
	pt->death_occured = sem_open("./death.sem", O_CREAT, 0644, 0);
	pt->philos_all_full = sem_open("./boated_philos.sem", O_CREAT, 0644, 0);
	pt->print_lock = sem_open("./print.sem", O_CREAT, 0644, 1);
	return (-(pt->forks == SEM_FAILED || pt->death_occured == SEM_FAILED
		|| pt->philos_all_full == SEM_FAILED || pt->print_lock == SEM_FAILED));
}

void	*plato_count_bloated_philos(void *plato_p)
{
	t_plato	*pt;

	pt = (t_plato *)plato_p;
	while (pt->bloat_counter < pt->np)
	{
		sem_wait(pt->philos_all_full);
		pt->bloat_counter++;
	}
	return (NULL);
}

int	plato_init(t_plato *pt, int argc, char **argv)
{
	int		i;
	pid_t	pid;

	printf("plato init : entered \n");
	if (parse_inputs(pt, argc, argv) < 0)
		return (repport_parsing_error());
	printf("plato init : parsing SUCCESSFULL \n");
	printf("plato init : nb philos : %d, time to die : %zd, time to eat : %zd, time to sleep : %zd, nb meals : %zd\n", pt->np, pt->delays[0], pt->delays[1], pt->delays[2], pt->delays[3]);
	if (plato_init_semaphores(pt) == -1)
	{
		printf("plate init : semophores open failed !\n");
		return (repport_semaphore_error());
	}
//	printf("plato init : malloc philos, forks and log pool SUCCESSFULL \n");
	i = -1;
	while (++i < pt->np)
	{
		pid = fork();
		if (pid < 0)
			return (repport_fork_error());
		else if (pid == 0)
		{
			philo_init(pt, &pt->ph, i);
			usleep(200);
			philo_routine(&pt->ph);
		}
		printf("plato init : fork %d\n", i);
	}
	printf("plato init : all fork started\n");
	if (pthread_create(&pt->bloat_counter_th, NULL, plato_count_bloated_philos, pt))
		return (repport_thread_init_error());
	printf("plato init : init philos SUCCESSFULL \n");
	return (0);
}

int	main(int argc, char **argv)
{
	static const char	*log_msg[5] = {"has taken a fork\n", "is eating\n", "is sleeping\n", "is thinking\n", "died\n"};
	t_plato				plato;
	int					i;
	
	ft_memclear(&plato, sizeof(plato));
	printf("main : t_plato declared variable plato was cleared\n");
	plato.log_msg = log_msg;
	i = -1;
	while (++i < 5)
		plato.log_msg_len[i] = (int)ft_strlen(log_msg[i]);
	if (plato_init(&plato, argc, argv) < 0)
	{
		printf("main : plato init is all fucked up\n");
		return (plato_clear(&plato, 1));
	}
	if (plato.death_occured)
		sem_wait(plato.death_occured);
	return (plato_clear(&plato, EXIT_SUCCESS));
}
