# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/01 17:58:19 by shunwata          #+#    #+#              #
#    Updated: 2025/07/01 20:57:47 by shunwata         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = big5_machine.out
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(FT_PRINTF_DIR)/includes -I $(LIBFT_DIR)

SRC = main.c
OBJ = $(SRC:.c=.o)

FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
FT_PRINTF_DIR = ft_printf

LIBFT_DIR = $(FT_PRINTF_DIR)/Libft

all: $(NAME)

$(NAME): $(OBJ) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(FT_PRINTF)

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(FT_PRINTF_DIR) clean

fclean:
	rm -f $(NAME)
	$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
