# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/10 05:57:29 by juan-her          #+#    #+#              #
#    Updated: 2025/12/12 16:02:24 by juan-her         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
NAME = philo
SRC = main.c init.c utils.c utils_esp.c philo.c
OBJ_URL = ./obj
OBJ = $(SRC:%.c=$(OBJ_URL)/%.o)
RM = rm -fr

all: $(NAME)
	@echo "$(NAME) ready"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "Finish $(NAME)"

$(OBJ_URL):
	@mkdir -p $(OBJ_URL)

$(OBJ_URL)/%.o: %.c | $(OBJ_URL)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ) $(OBJ_URL)
	@echo "Objects deleted";

fclean: clean
	@$(RM) $(NAME)
	@echo "Program deleted"

re: fclean all
	@echo "Re program"

.PHONY: all clean fclean re