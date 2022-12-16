# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 12:22:31 by tdehne            #+#    #+#              #
#    Updated: 2022/12/16 12:22:38 by tdehne           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-g -Werror -Wextra -Wall #-fsanitize=thread

NAME 		=	philo

INC_DIR		=	inc/
SRC_DIR		=	src/
OBJ_DIR		=	obj/
LIB_DIR		=	libft/

SRC_NAME	=	philo utils init activities end ft_atoi
INC_NAME	=	philo.h

SRC_FILES	=	$(addsuffix .c, $(addprefix $(SRC_DIR), $(SRC_NAME)))
LIB_FILE	=	$(addprefix $(LIB_DIR), $(LIB_NAME))
OBJ_FILES	=	$(addsuffix .o, $(addprefix $(OBJ_DIR), $(SRC_NAME)))
INC_FILES	=	$(addprefix $(INC_DIR), $(INC_NAME))

all : $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ_DIR) $(OBJ_FILES) 
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all