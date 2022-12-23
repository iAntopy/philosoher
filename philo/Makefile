
SRC_DIR			= ./src/
INCL_DIR			= ./incl/

_LFT_SRC		= ft_atol.c	\
				  ft_utils.c \
				malloc_free.c \
				ft_eprintf.c

_SRC		=	philo_main.c	\
				parse_inputs.c	\
				error_handling.c	\
				philo_life_cycle.c
#				philo_routine.c		

SRC_M		= $(addprefix $(SRC_DIR), $(_SRC))
LFT_SRC		= $(addprefix $(SRC_DIR), $(_LFT_SRC))

OBJ_M		= $(SRC_M:.c=.o) $(LFT_SRC:.c=.o)

INCL		= $(INCL_DIR)

CC			= gcc
CFLAGS		= -pthread -Wall -Wextra -Werror -g #-fsanitize=thread

NAME		= philo

%.o:		%.c
		-$(CC) $(CFLAGS) -I$(INCL) -c $< -o $@

$(NAME):	$(OBJ_M)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ_M)

all:		$(NAME)

clean:
		rm -f $(OBJ_M)

fclean:		clean
		rm -f $(NAME)

re:			fclean all
