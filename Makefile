# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 17:19:52 by elvmarti          #+#    #+#              #
#    Updated: 2022/02/02 19:37:15 by gaguado-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -O3#-g3 -fsanitize=address

NAME = minishell
DEBUG_NAME = minishell_debug
INCLUDES = includes/minishell.h
SOURCE_DIR= srcs
LIBFTPATH = ./libft/
LIBFTNAME = libft.a

SRCS = $(SOURCE_DIR)/minishell.c
OBJS = $(SRCS:.c=.o)

RM = rm -f

LIBFT = $(LIBFTPATH)$(LIBFTNAME)

$(NAME): $(OBJS) $(LIBFT)
		@echo $(PURPLE)Compiling ... $(RESET)
		$(CC) ${CFLAGS} ${OBJS} -I $(INCLUDES) -L. ${LIBFT} -lreadline -o ${NAME}

$(DEBUG_NAME): $(OBJS) $(LIBFT)
		@echo $(BLUE)Compiling debug... $(RESET)
		$(CC) ${CFLAGS} -I $(INCLUDES) -g ${SRCS} ${LIBFT} -lreadline -o ${DEBUG_NAME}

$(LIBFT):		
		@echo $(PURPLE)Libft $(RESET)
		make re -C $(LIBFTPATH)

all: $(NAME)

debug: $(DEBUG_NAME)

clean:
		@echo $(PURPLE)Cleaning ... $(RED)
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