# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/19 14:32:22 by lsohler           #+#    #+#              #
#    Updated: 2023/08/26 19:54:38 by lsohler          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# PROJET #
NAME = philo_bonus

# HEADER #
INCLUDES = includes/
HEADER_SRCS = philo.h
HEADER = $(addprefix $(INCLUDES), $(HEADER_SRCS))

# SOURCES #
SRCS = conditions.c error.c free.c init.c main.c philo.c utils.c
OBJS = $(SRCS:.c=.o)

# UTILS #
CC = gcc
FLAGS = -Wall -Werror -Wextra
#SANITIZE = -fsanitize=address -g3
#SANITIZE = -fsanitize=thread -g3
RM = rm -rf

# COLORS #
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
BLUE = \033[0;34m

# COMMANDS #
%.o: %.c
				@$(CC) $(FLAGS) $(SANITIZE) -I $(INCLUDES) -c $< -o $@


$(NAME): $(OBJS) $(LIBFT_OBJS)
				@$(CC) $(FLAGS) $(SANITIZE) -I $(INCLUDES) $(OBJS) $(LIBFT_OBJS) -o $(NAME)
				@echo "$(GREEN)$(NAME) compiled!$(DEFAULT)"


all: $(NAME)

norm:
				norminette *.c includes/ libft/

clean:
				@$(RM) $(OBJS)
				@$(RM) $(LIBFT_OBJS)
				@echo "$(YELLOW)object files cleaned!$(DEFAULT)"

fclean: clean
				@$(RM) $(NAME)
				@echo "$(RED)$(NAME) cleaned!$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re

