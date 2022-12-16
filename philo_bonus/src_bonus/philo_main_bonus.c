/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:13:18 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/15 21:52:45 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_get_bloat_count(t_plato *pt)
{
	int	ret;

	pthread_mutex_lock(&pt->bloat_counter_lock);
	ret = pt->bloat_counter;
	pthread_mutex_unlock(&pt->bloat_counter_lock);
	return (ret);
}

void	philo_add_bloated(t_plato *pt, int add_value)
{
	pthread_mutex_lock(&pt->bloat_counter_lock);
	pt->bloat_counter += add_value;
	pthread_mutex_unlock(&pt->bloat_counter_lock);
}

int	plato_clear(t_plato *pt, int ret_value)
{
	if (!pt)
		return (ret_value);
	usleep(50000);
	if (pt->death_occured)
		sem_post(pt->death_occured);
	if (pt->philos_all_full)
		sem_post(pt->philos_all_full);
	if (!pt->is_child_proc)
	{
		philo_add_bloated(pt, 1000000000);
		if (pt->bloat_counter_th)
			pthread_join(pt->bloat_counter_th, NULL);
		if (pt->np && pt->philo_pids)
			while (pt->np--)
				waitpid(pt->philo_pids[pt->np], NULL, 0);
		ft_free_p((void **)&pt->philo_pids);
		if (pt->max_meals)
			pthread_mutex_destroy(&pt->bloat_counter_lock);
	}
//	else
//		ft_memclear(pt, sizeof(t_plato));
	sem_close(pt->forks);
	sem_close(pt->death_occured);
	sem_close(pt->philos_all_full);
	sem_close(pt->print_lock);
	return (ret_value);
}

int	philo_init(t_plato *pt, t_philo *ph, int i)
{
//	printf("malloc init philos : calloc SUCCESSFULL\n");
	ph->nb_id = i;
	ph->__id_len = ft_putnbr_buff(ph->id, i + 1);
	ph->t_die = pt->t_die;
	ph->t_eat = pt->t_eat;
	ph->t_slp = pt->t_slp;
	ph->max_meals = pt->max_meals;
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
	pt->forks = sem_open(FORK_SEM_PATH, O_CREAT | O_EXCL, 0, pt->np);
	pt->death_occured = sem_open(DEATH_SEM_PATH, O_CREAT | O_EXCL, 0, 0);
	pt->philos_all_full = sem_open(BLOAT_SEM_PATH, O_CREAT | O_EXCL, 0, 0);
	pt->print_lock = sem_open(PRINT_SEM_PATH, O_CREAT | O_EXCL, 0, 1);
	if (pt->max_meals)
		pthread_mutex_init(&pt->bloat_counter_lock, NULL);
	
	sem_unlink(FORK_SEM_PATH);
	sem_unlink(DEATH_SEM_PATH);
	sem_unlink(BLOAT_SEM_PATH);
	sem_unlink(PRINT_SEM_PATH);
	
	ft_eprintf("sem init : post init status :\n");
	ft_eprintf("sem init : forks : %p\n", pt->forks);
	ft_eprintf("sem init : death_occured : %p\n", pt->death_occured);
	ft_eprintf("sem init : philos_all_full : %pn", pt->philos_all_full);
	ft_eprintf("sem init : print_lock : %p\n", pt->print_lock);
	return (-(pt->forks == SEM_FAILED || pt->death_occured == SEM_FAILED
		|| pt->philos_all_full == SEM_FAILED || pt->print_lock == SEM_FAILED));
}

void	*plato_count_bloated_philos(void *plato_p)
{
	t_plato	*pt;

	pt = (t_plato *)plato_p;
	while (philo_get_bloat_count(pt) < pt->np)
	{
		sem_wait(pt->philos_all_full);
		philo_add_bloated(pt, 1);
//		pt->bloat_counter++;
	}
	sem_wait(pt->print_lock);
	ft_eprintf("plato bloat counter : all philos are full ! Death occures\n");
	sem_post(pt->print_lock);
	sem_post(pt->death_occured);
	return (NULL);
}

int	plato_init(t_plato *pt, int argc, char **argv)
{
	int		i;
	pid_t	pid;

//	printf("plato init : entered \n");
	if (parse_inputs(pt, argc, argv) < 0)
		return (repport_parsing_error());
	if (plato_init_semaphores(pt) == -1)
	{
		printf("plate init : semophores open failed !\n");
		return (repport_semaphore_error());
	}
	if (!ft_malloc_p(sizeof(pid_t) * pt->np, (void **)&pt->philo_pids))
		return (repport_malloc_error());
	i = -1;
	while (++i < pt->np)
	{
		pid = fork();
		if (pid < 0)
			return (repport_fork_error());
		else if (pid == 0)
		{
			ft_free_p((void **)&pt->philo_pids);
			pt->is_child_proc = 1;
			philo_init(pt, &pt->ph, i);
//			usleep(200);
			philo_routine(&pt->ph);
//			ft_eprintf("CHILD : philo_routine DONE !\n");
			exit(plato_clear(pt, EXIT_SUCCESS));
		}
		pt->philo_pids[i] = pid;
//		printf("plato init : fork %d\n", i);
	}
	printf("plato init : all fork started\n");
	if (pt->max_meals && pthread_create(&pt->bloat_counter_th, NULL, plato_count_bloated_philos, pt))
		return (repport_thread_init_error());
//	printf("plato init : init philos SUCCESSFULL \n");
	return (0);
}

int	main(int argc, char **argv)
{
	static const char	*log_msg[5] = {
		"has taken a fork\n", "is eating\n",
		"is sleeping\n", "is thinking\n", "died\n"};
	t_plato				plato;
	int					i;
	
	ft_memclear(&plato, sizeof(plato));
//	printf("main : t_plato declared variable plato was cleared\n");
	plato.log_msg = log_msg;
	i = -1;
	while (++i < 5)
		plato.log_msg_len[i] = (int)ft_strlen(log_msg[i]);
	if (plato_init(&plato, argc, argv) < 0)
		return (plato_clear(&plato, EXIT_FAILURE));
	if (plato.death_occured)
		sem_wait(plato.death_occured);
	return (plato_clear(&plato, EXIT_SUCCESS));
}
