# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 11:59:21 by tpicchio          #+#    #+#              #
#    Updated: 2024/03/22 10:36:31 by tpicchio         ###   ########.fr        #
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
		parsing.c	\


OBJS = $(patsubst %.c,.build/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo
	@echo "${BOLD}Created  -> ${RED}$(NAME)${NO_COLOR}"

.build/%.o: %.c | .build
	@$(CC) $(CFLAGS) -c $< -o $@

.build:
	@mkdir -p $@ 

clean:
		@if [ -d .build ]; then \
			rm -rf .build; \
			echo; \
			echo "${BOLD}${YELLOW}Cleaned object files${NO_COLOR}"; \
		elif [ -e $(NAME) ] || [ ! -d .build ]; then \
			echo; \
			echo "${BOLD}${GREEN}Nothing to be done for clean${NO_COLOR}"; \
		fi

fclean: clean
		if [ -e $(NAME) ]; then \
			rm -f $(NAME); \
			echo; \
			echo "${BOLD}${YELLOW}Removed -> ${RED}${NAME}${NO_COLOR}"; \
		else \
			echo; \
			echo "${BOLD}${GREEN}Nothing to be done for fclean${NO_COLOR}"; \
		fi
re: fclean all

.PHONY: all clean fclean re

.SILENT: clean fclean re


NO_COLOR		=	\033[0m
BOLD			=	\033[1m
YELLOW			=	\033[33m
GREEN			=	\033[32m
BLUE			=	\033[34m
RED				=	\033[31m
