# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 17:19:52 by elvmarti          #+#    #+#              #
#    Updated: 2022/02/27 13:50:23 by gaguado-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

READLINE_INSTALL_LOCATION = $(shell brew --prefix readline)
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I $(READLINE_INSTALL_LOCATION)/include #-O3-g3 -fsanitize=address

NAME = minishell
DEBUG_NAME = minishell_debug
INCLUDES = includes/minishell.h
SOURCE_DIR= srcs
SOURCE_BUILT = $(SOURCE_DIR)/builtins
SOURCE_NON_BUILT = $(SOURCE_DIR)/non_builtins
SOURCE_PARS = $(SOURCE_DIR)/parser
SOURCE_UTILS = $(SOURCE_DIR)/utils
LIBFTPATH = ./libft/
LIBFTNAME = libft.a

SRCS = $(SOURCE_DIR)/minishell.c \
		$(SOURCE_PARS)/parse.c \
		$(SOURCE_PARS)/malloc_parse.c \
		$(SOURCE_PARS)/dollar_control.c \
		$(SOURCE_DIR)/signal_handlers.c \
		$(SOURCE_UTILS)/array_utils.c \
		$(SOURCE_UTILS)/string_utils.c \
		$(SOURCE_UTILS)/print_name.c \
		$(SOURCE_NON_BUILT)/search_program_on_path.c \
		$(SOURCE_NON_BUILT)/process_spawning_handling.c \
		$(SOURCE_BUILT)/pwd.c \
		$(SOURCE_BUILT)/echo.c \
		$(SOURCE_BUILT)/export.c \
		$(SOURCE_BUILT)/env.c \
		$(SOURCE_BUILT)/unset.c \
		$(SOURCE_BUILT)/exit.c \
		$(SOURCE_BUILT)/cd.c


OBJS = $(SRCS:.c=.o)

RM = rm -f

LIBFT = $(LIBFTPATH)$(LIBFTNAME)

$(NAME): $(OBJS) $(LIBFT)
		@echo $(PURPLE)- Compiling - $(RESET)
		$(CC) ${CFLAGS} -O3 ${OBJS} -I $(INCLUDES) -L. ${LIBFT} -lreadline -L $(READLINE_INSTALL_LOCATION)/lib -o ${NAME}

$(DEBUG_NAME): $(OBJS) $(LIBFT)
		@echo $(BLUE)- Compiling debug - $(RESET)
		$(CC) ${CFLAGS} -I $(INCLUDES) -g ${SRCS} ${LIBFT} -lreadline -L $(READLINE_INSTALL_LOCATION)/lib -o ${DEBUG_NAME}

$(LIBFT):		
		@echo $(PURPLE)Libft $(RESET)
		make re -C $(LIBFTPATH)

all: $(NAME)

debug: $(DEBUG_NAME)

clean:
		@echo $(PURPLE) - Cleaning - $(RED)
		$(RM) $(OBJS) $(LIBFTPATH)*.o

fclean: clean
		$(RM) $(NAME) $(LIBFT)

re: fclean all

#Colors
BLACK		:="\033[0;30m"
RED			:="\033[0;31m"
GREEN		:="\033[0;32m"
BROWN		:="\033[0;33m"
BLUE		:="\033[0;34m"
PURPLE		:="\033[0;35m"
CYAN		:="\033[0;36m"
LIGHT_GRAY	:="\033[0;37m"
DARK_GRAY	:="\033[1;30m"
LIGHT_RED	:="\033[1;31m"
LIGHT_GREEN	:="\033[1;32m"
YELLOW		:="\033[1;33m"
LIGHT_BLUE	:="\033[1;34m"
LIGHT_PURPLE:="\033[1;35m"
LIGHT_CYAN	:="\033[1;36m"
WHITE		:="\033[1;37m"
RESET		:="\x1b[0m"

.PHONY: all debug clean fclean re