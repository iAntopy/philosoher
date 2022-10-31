/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:13:18 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/31 04:34:30 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	plato_clear(t_plato *pt, int ret_value)
{
	int	i;

	if (!pt)
		return (ret_value);
	usleep(50000);
	printf("plato clear : entered \n");
	
	pt->death_occured = 1;
	i = -1;
	while (++i < pt->np)
	{
		printf("plato clear : %d - joining thread %zu\n", i, pt->philos[i].thread_id);
		if (pt->philos[i].thread_id)
			pthread_join(pt->philos[i].thread_id, NULL);
	}
	printf("plato clear : all threads joined SUCCESSFULLY (if possible) \n");
	
	if (pt->philos)
		ft_free_p((void **)&pt->philos);
	printf("plato clear : philos freed SUCCESSFULLY \n");
	
	if (pt->forks)
	{
		i = -1;
		while (++i < pt->np)
			pthread_mutex_destroy(pt->forks + i);
		ft_free_p((void **)&pt->forks);
	}
	pthread_mutex_destroy(&pt->print_lock);
//	printf("plato clear : forks (mutexes) destroyed and freed SUCCESSFULLY \n");

//	logs_clear(&pt->logs, &pt->queue_lock);
//	logs_clear(&pt->logs_pool, &pt->pool_lock);
//	printf("plato clear : event logs and log pool cleared SUCCESSFULLY \n");
	
//	pthread_mutex_destroy(&pt->queue_lock);
//	pthread_mutex_destroy(&pt->pool_lock);
//	printf("plato clear : queue lock and pool lock destroyed SUCCESSFULLY \n");
	return (ret_value);
}
/*
int	plato_send_forth_legion_of_pasta_eaters(t_plato *pt)
{
	int	i;

	if (!pt)
		return (-1);
	printf("send forth legion : releasing the hounds\n");
	i = -1;
	while (++i < pt->np)
		if (pthread_kill(pt->philos[i].thread_id, SIGCONT) < 0)
			return (-1);
	Printf("send forth legion : release SUCCESSFULL\n");
	return (0);
}
*/

int	plato_malloc_and_init_all_forks(t_plato *pt)
{
	pthread_mutex_t	*fs;

	fs = NULL;
	if (!pt || !ft_calloc_p(sizeof(pthread_mutex_t) * pt->np, (void **)&fs))
		return (-1);
	pt->forks = fs;
	while ((fs - pt->forks) < pt->np)
		if (pthread_mutex_init(fs++, NULL) != 0)
			return (-1);
	return (0);
}

int	plato_malloc_and_init_all_philos(t_plato *pt)
{
	t_philo	*philos;
	t_philo	*ph;
	int	i;

	philos = NULL;
	printf("malloc init philos : entered. plato ptr : %p, nb philos %d, sizeof(t_philo) : %zu\n", pt, pt->np, sizeof(t_philo));
	if (!pt || !ft_calloc_p(sizeof(t_philo) * pt->np, (void **)&philos))
		return (-1);
//	printf("malloc init philos : calloc SUCCESSFULL\n");
	i = -1;
	while (++i < pt->np)
	{
		ph = philos + i;
		ph->death_occured = &pt->death_occured;
		ph->__id_len = ft_putnbr_buff(ph->id, i + 1);
		ph->delays = pt->delays;
		ph->log_msg = pt->log_msg;
		ph->log_msg_len = (const int *)pt->log_msg_len;
		ph->left_fork = pt->forks + ((i + (i % 2)) % pt->np);
		ph->right_fork = pt->forks + ((i + !(i % 2)) % pt->np);
		ph->print_lock = &pt->print_lock;
//		ph->queue_lock = &pt->queue_lock;
//		ph->pool_lock = &pt->pool_lock;
//		ph->logs = &pt->logs;
//		ph->logs_pool = &pt->logs_pool;
//		printf("malloc init philos : philo %i setup SUCCESSFULL\n", i);
	}
	pt->philos = philos;
//	printf("malloc init philos : return SUCCESSFULL\n");
	return (0);
}

int	plato_init(t_plato *pt, int argc, char **argv)
{
	int	i;
	printf("plato init : entered \n");
	if (parse_inputs(pt, argc, argv) < 0)
		return (repport_parsing_error());
	printf("plato init : parseing SUCCESSFULL \n");
	pt->print_delay = plato_find_min_print_delay(pt);
//	if (pthread_mutex_init(&pt->queue_lock, NULL) != 0
//		|| pthread_mutex_init(&pt->pool_lock, NULL) != 0)
//		return (repport_mutex_error());
	if (pthread_mutex_init(&pt->print_lock, NULL) != 0)
		return (-1);
	printf("plato init : nb philos : %d, time to die : %zd, time to eat : %zd, time to sleep : %zd, nb meals : %zd\n", pt->np, pt->delays[0], pt->delays[1], pt->delays[2], pt->delays[3]);
	if (!ft_calloc_p(sizeof(t_philo) * pt->np, (void **)&pt->philos)
		|| plato_malloc_and_init_all_forks(pt) < 0
//		|| plato_create_log_pool(pt) < 0
		|| plato_malloc_and_init_all_philos(pt) < 0)
	{
		printf("plate init : either malloc forks, malloc philos or malloc logs pool fucked up !\n");
		return (repport_malloc_error());
	}
//	printf("plato init : malloc philos, forks and log pool SUCCESSFULL \n");
	i = 0;
	while (i < pt->np)
	{
		if (pthread_create(&(pt->philos[i].thread_id), NULL, philo_living_life, pt->philos + i) != 0)
			return (repport_thread_init_error());
		i += 2;
	}
	i = 1;
	while (i < pt->np)
	{
		if (pthread_create(&(pt->philos[i].thread_id), NULL, philo_living_life, pt->philos + i) != 0)
			return (repport_thread_init_error());
		i += 2;
	}
//	printf("plato init : init philos SUCCESSFULL \n");
	return (0);
}

int	main(int argc, char **argv)
{
	static const char	*log_msg[5] = {"has taken a fork\n", "is eating\n", "is sleeping\n", "is thinking\n", "died\n"};
	t_plato				plato;
	int				i;
	
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
//	printf("main : plato init was SUCCESSFULL !\n");
//	plato_print(&plato);
	while (!plato.death_occured)
//	{
		usleep(plato.print_delay);
//		plato_print_logs(&plato);
//	}
	return (plato_clear(&plato, EXIT_SUCCESS));
}
