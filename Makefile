# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 12:22:31 by tdehne            #+#    #+#              #
#    Updated: 2022/12/21 09:42:47 by tdehne           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Werror -Wextra -Wall# -fsanitize=thread -g

BOLD	= \033[1m
BLACK	= \033[30;1m
RED		= \033[31;1m
GREEN	= \033[32;1m
YELLOW	= \033[33;1m
BLUE	= \033[34;1m
MAGENTA	= \033[35;1m
CYAN	= \033[36;1m
WHITE	= \033[37;1m
RESET	= \033[0m

NAME 		=	philo

INC_DIR		=	inc/
SRC_DIR		=	src/
OBJ_DIR		=	obj/
LIB_DIR		=	libft/

SRC_NAME	=	philo utils init activities end ft_atoi death
INC_NAME	=	philo.h

SRC_FILES	=	$(addsuffix .c, $(addprefix $(SRC_DIR), $(SRC_NAME)))
LIB_FILE	=	$(addprefix $(LIB_DIR), $(LIB_NAME))
OBJ_FILES	=	$(addsuffix .o, $(addprefix $(OBJ_DIR), $(SRC_NAME)))
INC_FILES	=	$(addprefix $(INC_DIR), $(INC_NAME))

header		=	.header

all : $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@echo "$(BLUE)Compiling: $(RESET) $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(header) $(OBJ_DIR) $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)
	@echo "$(GREEN)Done$(RESET)"

$(header) :
	@touch .header
	@echo	"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░"
	@echo	"░████████╗██████╗░███████╗██╗░░██╗███╗░░██╗███████╗░"
	@echo	"░╚══██╔══╝██╔══██╗██╔════╝██║░░██║████╗░██║██╔════╝░"
	@echo	"░░░░██║░░░██║░░██║█████╗░░███████║██╔██╗██║█████╗░░░"
	@echo	"░░░░██║░░░██║░░██║██╔══╝░░██╔══██║██║╚████║██╔══╝░░░"
	@echo	"░░░░██║░░░██████╔╝███████╗██║░░██║██║░╚███║███████╗░"
	@echo	"░░░░╚═╝░░░╚═════╝░╚══════╝╚═╝░░╚═╝╚═╝░░╚══╝╚══════╝░"
	@echo	"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░"

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME) .header

re: fclean all