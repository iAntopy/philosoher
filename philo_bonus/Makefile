# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/01 20:35:26 by iamongeo          #+#    #+#              #
#    Updated: 2022/12/16 17:52:27 by iamongeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCL_DIR		= ./incl/
SRC_DIR			= ./src_bonus/

_LFT_SRC		= ft_utils.c \
				  ft_atol.c	\
				  malloc_free.c	\
				  ft_eprintf.c

_SRC		=	philo_main_bonus.c	\
				parse_inputs_bonus.c	\
				logging_bonus.c		\
				error_handling_bonus.c	\
				philo_routine_bonus.c		
#				timer_bonus.c		
#				print_funcs_bonus.c
#				log_pool_utils.c	

SRC_B		= $(addprefix $(SRC_DIR), $(_SRC))
LFT_SRC		= $(addprefix $(SRC_DIR), $(_LFT_SRC))

OBJ_B		= $(SRC_B:.c=.o) $(LFT_SRC:.c=.o)

INCL		= $(INCL_DIR)

CC			= gcc
CFLAGS		= -pthread -Wall -Wextra -Werror -g -fsanitize=thread

NAME_BONUS		= philo_bonus

%.o:		%.c
		-$(CC) $(CFLAGS) -I$(INCL) -c $< -o $@

$(NAME_BONUS):	$(OBJ_B)
		$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_B)

all:		$(NAME_BONUS)

clean:
		rm -f $(OBJ_B)

fclean:		clean
		rm -f $(NAME_BONUS)

re:			fclean all
