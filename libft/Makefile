# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/10 17:30:38 by elvmarti          #+#    #+#              #
#    Updated: 2021/05/13 19:53:33 by elvmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SONAME = libft.so
CC = gcc
FLAGS = -Wall -Wextra -Werror -I. -c 
FILES = ft_memset.c ft_strrchr.c \
					ft_bzero.c ft_strnstr.c \
					ft_memcpy.c ft_strncmp.c \
					ft_memccpy.c ft_atoi.c \
					ft_memmove.c ft_isalpha.c \
					ft_memchr.c ft_isdigit.c \
					ft_memcmp.c ft_isalnum.c \
					ft_strlen.c ft_isascii.c \
					ft_strlcpy.c ft_isprint.c \
					ft_strlcat.c ft_toupper.c \
					ft_strchr.c ft_tolower.c \
					ft_calloc.c ft_strdup.c \
					ft_substr.c ft_strcmp.c \
					ft_strjoin.c \
					ft_strtrim.c \
					ft_split.c \
					ft_itoa.c \
					ft_strmapi.c \
					ft_putchar_fd.c \
					ft_putstr_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \
					get_next_line.c \
					ft_lstnew.c \
					ft_lstadd_front.c \
					ft_lstsize.c \
					ft_lstlast.c \
					ft_lstadd_back.c \
					ft_lstdelone.c \
					ft_lstclear.c \
					ft_lstiter.c \
					ft_lstmap.c

FILES_BONUS = 		ft_lstnew.c \
					ft_lstadd_front.c \
					ft_lstsize.c \
					ft_lstlast.c \
					ft_lstadd_back.c \
					ft_lstdelone.c \
					ft_lstclear.c \
					ft_lstiter.c \
					ft_lstmap.c

OBJ = $(FILES:%.c=%.o)

OBJ_BONUS = $(FILES_BONUS:%.c=%.o)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ): $(FILES)
	gcc $(FLAGS) $(FILES)

bonus: $(OBJ) $(OBJ_BONUS)
		ar rcs $(NAME) $(NAME_BONUS) $(OBJ) $(OBJ_BONUS) 

all: $(NAME)

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)
	rm -f $(SONAME)

re: fclean all

so:
	gcc -shared -o $(SONAME) -fPIC $(FILES) $(FILES_BONUS)

.PHONY: all clean fclean re so bonus
