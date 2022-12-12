/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:13:41 by iamongeo          #+#    #+#             */
/*   Updated: 2022/12/10 20:24:36 by iamongeo         ###   ########.fr       */
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

typedef struct	s_philo
{
	pthread_t		tid;
	int				nb_id;
	char			id[32];
	int				__id_len;
	ssize_t			t_eat;
	ssize_t			t_slp;
	ssize_t			nb_meals;
	char			*death_occured;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_lock;
	const char		**log_msg;
	const int		*log_msg_len;
	t_tv			t0;
	t_tv			pasta_t;
	ssize_t			t_offset;
}	t_philo;

typedef struct	s_plato
{
	int				np;				// nb of philosopher
	ssize_t			t_die;
	ssize_t			t_eat;
	ssize_t			t_slp;
	ssize_t			max_meals;
	char			death_occured;
	t_philo			*philos;		// array of philosopher structs. len = np.
	pthread_t		coach;			// thread checking times 
	pthread_mutex_t	*forks;			// Array of mutexes. len = np
	pthread_mutex_t	print_lock;
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
int		ft_putnbr_buff(char *buff, ssize_t nbr); // returns len of str in buff
size_t	ft_strlen(const char *str);
int		ft_isdigit(int c);
void	ft_memclear(void *dst, size_t size);
int		ft_eprintf(const char *fmt, ...);
ssize_t	timer_us(t_tv *t0);

/////////// PHILOSOPHER FUNCS //////////
int		parse_inputs(t_plato *pt, int argc, char **argv);
int		philo_log(t_philo *ph, int event);
void	*coach_overlooking_steaming_brains(void *plato_p);
void	*philo_living(void *ph);
//ssize_t	plato_find_min_print_delay(t_plato *pt);

////////// PRINT FUNCS /////////////
void	philo_print(t_philo *ph);
void	plato_print(t_plato *pt);

////////// ERROR HANDLING ////////////
int		repport_malloc_error(void);
int		repport_mutex_error(void);
int		repport_parsing_error(void);
int		repport_thread_init_error(void);

#endif
