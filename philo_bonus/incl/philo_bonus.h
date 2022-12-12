/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:13:41 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/11 23:38:19 by iamongeo         ###   ########.fr       */
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
# include <semaphore.h>
# include <stdio.h>
# include <limits.h>

# define CYAN_C		"\033[0;36m"
# define WHITE_C	"\033[0;37m"
# define RED_BC		"\033[1;31m"
# define CYAN_BC	"\033[1;36m"
# define WHITE_BC	"\033[1;37m"

# define X_BASE "0123456789abcdef"
# define XX_BASE "0123456789ABCDEF"
# define DEC_BASE "0123456789"

# define FORK_SEM_PATH "./sems/forks.sem"
# define DEATH_SEM_PATH "./sems/death.sem"
# define BLOAT_SEM_PATH "./sems/bloated.sem"
# define PRINT_SEM_PATH "./sems/print.sem"

typedef struct timeval	t_tv;

typedef struct	s_philo
{
	int				nb_id;
	char			id[32];
	int				__id_len;
	ssize_t			*delays;
	int				is_dead;
	int				is_full;
	sem_t			*death_occured;
	sem_t			*philos_all_full;
	sem_t			*forks;
	sem_t			*print_lock;
	const char		**log_msg;
	const int		*log_msg_len;
	t_tv			t0;
	t_tv			pasta_t;
	ssize_t			nb_meals;
}	t_philo;

typedef struct	s_plato
{
	int				np;				// nb of philosopher
	ssize_t			delays[4];		// delays[0] : time to die, delay[1] : time to eat, delays[2] : time to sleep.
	t_philo			ph;
	pthread_t		bloat_counter_th;
	int				bloat_counter;
	sem_t			*death_occured;
	sem_t			*philos_all_full;
	sem_t			*forks;
	sem_t			*print_lock;
	const char		**log_msg;	// const strings array holding log messages.
	int				log_msg_len[5];	// const int indicating length of log_msg
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
int		ft_putnbr_buff(char *buff, ssize_t nbr);	// returns len of nbr str in buff
size_t	ft_strlen(const char *str);
int		ft_isdigit(int c);
void	ft_memclear(void *dst, size_t size);
int		ft_eprintf(const char *fmt, ...);
ssize_t	timer_ms(t_tv *t0);

/////////// PHILOSOPHER FUNCS //////////
int		parse_inputs(t_plato *pt, int argc, char **argv);
int		philo_log_event(t_philo *ph, int event);
//void	*coach_overlooking_steaming_brains(void *plato_p);
void	philo_routine(t_philo *ph);
//ssize_t	plato_find_min_print_delay(t_plato *pt);

////////// PRINT FUNCS /////////////
//void	philo_print(t_philo *ph);
//void	plato_print(t_plato *pt);

////////// ERROR HANDLING ////////////
int		repport_parsing_error(void);
int		repport_thread_init_error(void);
int		repport_fork_error(void);
int		repport_thread_init_error(void);
int		repport_semaphore_error(void);

#endif
