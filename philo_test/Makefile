NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

SRCS =	main.c \
		init_data.c \
		utils.c \
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
			echo "${BOLD}${BLUE}Nothing to be done for clean${NO_COLOR}"; \
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