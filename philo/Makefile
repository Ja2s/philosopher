# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 16:20:16 by jgavairo          #+#    #+#              #
#    Updated: 2024/07/21 18:09:17 by jgavairo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
PATH_SRC = src/

SRCS =	$(PATH_SRC)philo.c \
		$(PATH_SRC)utils.c \
		$(PATH_SRC)utils_nd.c \
		$(PATH_SRC)utils_rd.c \
		$(PATH_SRC)init.c \
		$(PATH_SRC)actions.c \
		$(PATH_SRC)libft.c
OBJS =$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re