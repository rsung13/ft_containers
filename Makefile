# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsung <rsung@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/29 10:51:44 by rsung             #+#    #+#              #
#    Updated: 2022/12/29 16:15:30 by rsung            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = exec

CC = c++

FLAGS = -Wextra -Werror -Wall -g -std=c++98

SRCS = ft_main.cpp

SRCS_DIR = srcs

OBJS_DIR = objs

INCLUDE = -I./include

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))

all : $(NAME)

$(NAME) : $(OBJS_DIR) $(OBJS)
	$(CC) $(FLAGS) $(INCLUDE) -o $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean :
	rm -rf $(OBJS_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean
