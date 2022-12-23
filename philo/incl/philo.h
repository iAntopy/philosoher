/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:13:41 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/23 05:04:10 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <stdarg.h>
# include <stdio.h>

# define CYAN_C		"\033[0;36m"
# define WHITE_C	"\033[0;37m"
# define RED_BC		"\033[1;31m"
# define CYAN_BC	"\033[1;36m"
# define WHITE_BC	"\033[1;37m"

# define X_BASE "0123456789abcdef"
# define XX_BASE "0123456789ABCDEF"
# define DEC_BASE "0123456789"

typedef struct timeval	t_tv;

typedef struct s_limits
{
	ssize_t		t_die;
	ssize_t		t_eat;
	ssize_t		t_slp;
	int			max_meals;
}	t_limits;

typedef struct s_global_locks
{
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	meals;
}	t_glocks;

typedef struct s_forks
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}	t_forks;

typedef struct s_philo
{
	pthread_t		tid;
	int				nb_id;
	char			id[32];
	int				__id_len;
	t_limits		lims;
	ssize_t			nb_meals;
	int				*death_occured;
	int				*nb_hungry;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_forks			forks;
	t_glocks		*glocks;
	const char		**log_msg;
	const int		*log_msg_len;
	t_tv			pasta_t;
	t_tv			start_t;
	int				is_full;
	int				is_dead;
}	t_philo;

typedef struct s_plato
{
	int				total_philos;
	int				np;
	t_limits		lims;
	int				death_occured;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	t_glocks		glocks;
	int				nb_hungry;
	const char		**log_msg;
	int				log_msg_len[5];
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
int		ft_calloc_p(size_t size, void **ptr);
int		ft_free_p(void **ptr);
ssize_t	ft_atol(const char *str);
int		ft_putnbr_buff(char *buff, ssize_t nbr);
size_t	ft_strlen(const char *str);
int		ft_isdigit(int c);
void	ft_memclear(void *dst, size_t size);
int		ft_eprintf(const char *fmt, ...);
ssize_t	timer_us(t_tv *t0);

/////////// PHILOSOPHER FUNCS //////////
int		parse_inputs(t_plato *pt, int argc, char **argv);
int		philo_log(t_philo *ph, int event);
void	philo_wait_check(t_philo *ph, ssize_t time);
int		is_someone_dead(t_philo *ph);
int		is_someone_dead_check(t_philo *ph);
void	increment_nb_meals(t_philo *ph);
void	*philo_life_cycle(void *ph);
void	*philo_loner(void *ph);

////////// ERROR HANDLING ////////////
int		repport_malloc_error(void);
int		repport_mutex_error(void);
int		repport_parsing_error(void);
int		repport_thread_init_error(void);

#endif
