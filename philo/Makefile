# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 11:59:21 by tpicchio          #+#    #+#              #
#    Updated: 2024/03/20 12:10:04 by tpicchio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

SRCS =	main.c \
		setup.c \
		philosopher.c \
		utils.c \
		philo_life.c \
		supervisor.c	\


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -g $(CFLAGS) -o $(NAME) $(OBJS)
	echo
	echo "${BOLD}Created  -> ${RED}$(NAME)${NO_COLOR}"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		@if ls *.o > /dev/null 2>&1; then \
			rm -f $(OBJS); \
			echo; \
			echo "${BOLD}${YELLOW}Cleaned object files${NO_COLOR}"; \
		fi

fclean: clean
		if [ -e $(NAME) ]; then \
			rm -f $(NAME); \
			echo; \
			echo "${BOLD}${YELLOW}Removed -> ${RED}${NAME}${NO_COLOR}"; \
		fi
re: fclean all

.PHONY: all clean fclean re

.SILENT:


NO_COLOR		=	\033[0m
BOLD			=	\033[1m
YELLOW			=	\033[33m
GREEN			=	\033[32m
BLUE			=	\033[34m
RED				=	\033[31m
