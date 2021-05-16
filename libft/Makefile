# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnarwhal <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/05 13:35:13 by mnarwhal          #+#    #+#              #
#    Updated: 2019/09/05 13:35:16 by mnarwhal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

SRC = ft_putchar.c ft_putchar_fd.c ft_putendl_fd.c ft_putstr.c ft_putstr_fd.c \
					ft_putchar_mod.c ft_putstr_mod.c ft_strcmp.c

FLAGS = gcc -c -Wall -Wextra -Werror -g
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@$(FLAGS) $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
