
SRC_DIR			= philo/
SRC_B_DIR		= philo_bonus/

LFT_SRC			= ft_atoi.c	\
				  ft_deltatime_usec.c 	\
				  ft_memclear.c			\
				  malloc_free.c			\
				  ft_eprintf.c

_SRC		=	philo_main.c	\
				parse_inputs.c	\
				logging.c		\
				error_handling.c	\
				philo_thread.c		\
				print_funcs.c

#_SRC_B	=	checker_main_bonus.c

SRC_M		= $(addprefix $(SRC_DIR), $(_SRC) $(LFT_SRC))
#SRC_B		= $(addprefix $(SRC_B_DIR), $(_SRC_B))

OBJ_M		= $(SRC_M:.c=.o)
#OBJ_B		= $(SRC_B:.c=.o)

INCL		= philo/

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

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

$(LIBFT):
		make -C libft/

all:		$(NAME)

#bonus:		$(NAME_BONUS)

clean:
		rm -f $(OBJ_M) $(OBJ_B)

fclean:		clean
		rm -f $(NAME) $(NAME_BONUS)

re:			fclean all
