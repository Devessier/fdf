# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/11 10:38:02 by bdevessi          #+#    #+#              #
#    Updated: 2019/04/11 15:07:16 by bdevessi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CFLAGS = -g -Wall -Wextra -Werror -Iincludes -Ilibft/includes -I/usr/locale/include
CC = gcc

#include src.mk

SRCS = $(wildcard src/*.c)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

GREEN_TEXT = \x1b[92m
RED_TEXT = \x1b[92m
GREEN_BG = \x1b[102;30m
NO_COLOR = \x1b[0m

%.o: %.c Makefile src.mk includes/fdf.h
	@ echo "Compiling $(GREEN_TEXT)$*.c\x1b[0m..."
	@ $(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@ echo "Make libft..."
	@ $(MAKE) -C libft
	@ echo "Assemblating everything for $(GREEN_BG)$(NAME)$(NO_COLOR)..."
	@ $(CC) $(CFLAGS) -o $(NAME) $(OBJS) libft/libft.a -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit
	@ echo "$(GREEN_BG)$(NAME)$(NO_COLOR) is done ! \xE2\x9C\x85"

clean:
	@ rm -f $(OBJS)
	@ echo "Cleaning $(GREEN_BG)$(NAME)$(NO_COLOR) done !"

fclean: clean
	@rm -f $(NAME)
	@ echo "Super cleaning $(GREEN_BG)$(NAME)$(NO_COLOR) done !"

re: fclean $(NAME)

.PHONY: clean fclean re proto
