# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 14:06:21 by ogokkaya          #+#    #+#              #
#    Updated: 2024/02/19 17:28:10 by ogokkaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc 

CFLAGS = -Wall -Werror -Wextra

SRC = pipex.c  path_find.c


$(NAME): $(SRC)
	@echo "\nCompiling the program files...\n"
	@make -s -C libft
	@$(CC) $(CFLAGS) $(SRC) libft/libft.a -o $(NAME)
all:	$(NAME)

clean:
	@find . -type f \( -name "*.o" \) -delete

fclean: clean
	@find . -type f \( -name "*.a" -o -name "pipex" \) -delete

re: fclean all

.PHONY: fclean re clean all
