# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/01 16:28:15 by tvalimak          #+#    #+#              #
#    Updated: 2024/03/14 11:40:05 by tvalimak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a

SRCS = \
	get_next_line_utils.c \
	get_next_line.c \

OBJS := $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	cc $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJS)
	ar -rcs $(NAME) $^ 
	@echo "$(GREEN)gnl compiled!$(NC)"

all: $(NAME)

clean: 
	rm -f $(OBJS)
	@echo "$(YELLOW)The gnl object files have been removed!$(NC)"

fclean: 
	rm -f $(NAME) $(OBJS)
	@echo "$(YELLOW)All the gnl files have been removed!$(NC)"

re: fclean all

.PHONY: all clean fclean re

#colours
GREEN = \033[0;92m
YELLOW = \033[0;93m
CYAN = \033[0;96m
NC = \033[0m
