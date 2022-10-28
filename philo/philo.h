/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:13:41 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/28 00:07:34 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <stdio.h>

# define CYAN_C		"\033[0;36m"
# define WHITE_C	"\033[0;37m"

# define RED_BC		"\033[1;31m"
# define CYAN_BC	"\033[1;36m"
# define WHITE_BC	"\033[1;37m"

typedef struct	s_log_info
{
	int					id;
	ssize_t				timestamp;
	char				event;
	struct s_log_info	*next;
}	t_log;

typedef struct	s_philo
{
	int				id;
	ssize_t			*delays;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*queue_lock;
	t_log			*logs;
	ssize_t			cumul_time;
	ssize_t			ts_last_meal;
}	t_philo;

typedef struct	s_plato
{
	int		np;				// nb of philosopher
	ssize_t	delays[4];		// delays[0] : time to die, delay[1] : time to eat, delays[2] : time to sleep.
	t_philo			*philos;		// array of philosopher structs. len = np.
	pthread_mutex_t	*forks;			// array of mutexes. len = np
	pthread_mutex_t	queue_lock;		// single log for event logger.
	t_log			*logs;
	const char		*log_msg;
}	t_plato;

enum	e_philo_events
{
	PH_FRK = 0,
	PH_EAT = 1,
	PH_SLP = 2,
	PH_THK = 3,
	PH_DIE = 4
};

///////////// LIBFT /////////////
int		ft_malloc_p(size_t size, void **ptr);
int		ft_free_p(void **ptr);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	ft_memclear(void *dst, size_t size);
int		ft_eprintf(const char *fmt, ...);

#endif
