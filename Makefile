# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/04 16:13:54 by ybarbier          #+#    #+#              #
#    Updated: 2017/06/08 15:56:38 by ybarbier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#____________CONFIG____________#

NAME_NM = ft_nm
NAME_OTOOL = ft_ottol

PATH_SRC = ./src/

PATH_INC = ./inc/

PATH_INC_LIBFT = ./libft/includes/

INCLUDES = -I $(PATH_INC) -I $(PATH_INC_LIBFT)

CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES) -g
LIBS = -L libft/ -lft -lm

#____________FILES____________#

SRC =	main.c 

OBJ = $(addprefix $(PATH_SRC), $(SRC:.c=.o))

#____________RULES____________#

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $(OBJ) -o $(NAME_NM) $(LIBS)


#___CLEAN___#

clean:
	rm -f $(OBJ)

#___FCLEAN___#

fclean: clean
	rm -f $(NAME)

#___RE___#

re: fclean all
