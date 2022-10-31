
SRC_DIR			= ./

_LFT_SRC			= ft_atol.c	\
				  ft_strlen.c	\
				  ft_putnbr_buff.c	\
				  ft_isdigit.c		\
				  ft_memclear.c			\
				  malloc_free.c			\
				  ft_eprintf.c

_SRC		=	philo_main.c	\
				parse_inputs.c	\
				logging.c		\
				error_handling.c	\
				philo_thread.c		\
				timer.c			\
				print_funcs.c		\
#				log_pool_utils.c	

SRC_M		= $(addprefix $(SRC_DIR), $(_SRC))
LFT_SRC		= $(addprefix $(SRC_DIR), $(_LFT_SRC))

OBJ_M		= $(SRC_M:.c=.o) $(LFT_SRC:.c=.o)

INCL		= $(SRC_DIR)

CC		= gcc
CFLAGS		= -pthread -Wall -Wextra -Werror

NAME		= philo

%.o:		%.c
		-$(CC) $(CFLAGS) -I$(INCL) -c $< -o $@

$(NAME):	$(OBJ_M)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ_M)

all:		$(NAME)

clean:
		rm -f $(OBJ_M) $(OBJ_B)

fclean:		clean
		rm -f $(NAME) $(NAME_BONUS)

re:			fclean all
