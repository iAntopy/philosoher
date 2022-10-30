
SRC_DIR			= philo_m/
SRC_B_DIR		= philo_bonus/

_LFT_SRC			= ft_atoi.c	\
				  ft_isdigit.c		\
				  ft_memclear.c			\
				  malloc_free.c			\
				  ft_eprintf.c

_SRC		=	philo_main.c	\
				parse_inputs.c	\
				logging.c		\
				log_pool_utils.c	\
				error_handling.c	\
				philo_thread.c		\
				timer.c			\
				print_funcs.c

#_SRC_B	=	checker_main_bonus.c

SRC_M		= $(addprefix $(SRC_DIR), $(_SRC))
LFT_SRC		= $(addprefix $(SRC_DIR), $(_LFT_SRC))
#SRC_B		= $(addprefix $(SRC_B_DIR), $(_SRC_B))

OBJ_M		= $(SRC_M:.c=.o) $(LFT_SRC:.c=.o)
#OBJ_B		= $(SRC_B:.c=.o)

INCL		= $(SRC_DIR)
INCL_B		= $(SRC_B_DIR)

CC			= gcc
CFLAGS		= -pthread -Wall -Wextra -Werror

NAME		= philo
NAME_BONUS	= philo_bonus

#%_bonus.o:	%.c
#		-$(CC) $(CFLAGS) -I$(INCL) -c $< -o $@
%.o:		%.c
		-$(CC) $(CFLAGS) -I$(INCL) -c $< -o $@

$(NAME):	$(OBJ_M)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ_M)

#$(NAME_BONUS):	$(OBJ_B)
#		$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_B)

all:		$(NAME)

#bonus:		$(NAME_BONUS)

clean:
		rm -f $(OBJ_M) $(OBJ_B)

fclean:		clean
		rm -f $(NAME) $(NAME_BONUS)

re:			fclean all
