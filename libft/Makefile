# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 15:13:35 by mpelage           #+#    #+#              #
#    Updated: 2024/06/03 18:26:56 by mpelage          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = $(shell find . -name 'ft_*' '!' -iname 'ft_lst*')
SRC_BONUS = $(shell find . -name 'ft_lst*')
OBJS = $(SRC:.c=.o)
OBJS_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -rf $(NAME)

bonus: $(OBJS) $(OBJS_BONUS)
	ar -rcs $(NAME) $(OBJS) $(OBJS_BONUS)
		
re: fclean all bonus

.PHONY: all clean fclean re bonus