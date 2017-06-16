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
NAME_OTOOL = ft_otool

PATH_SRC = ./src/

PATH_INC = ./inc/

PATH_INC_LIBFT = ./libft/includes/

INCLUDES = -I $(PATH_INC) -I $(PATH_INC_LIBFT)

CC = cc

ifeq ($(DEBUG),yes)
	CFLAGS = $(INCLUDES) -g
	LDFLAGS = -shared
else
	CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
	LDFLAGS = -shared
endif

LIBS = -L libft/ -lft -lm

#____________FILES____________#

SRC =	nm.c \
			utils.c \
			display.c \
			format_information.c \
			handler.c \
			init_format.c \
			section_list.c \
			symbol_list.c \
			ft_puthexa_size.c


OBJ = $(addprefix $(PATH_SRC), $(SRC:.c=.o))

#____________RULES____________#

.PHONY: clean fclean re

all: $(NAME_NM)

$(NAME_NM): $(OBJ)
	make -C libft/
	$(CC) $(OBJ) -o $(NAME_NM) $(LIBS)


#___CLEAN___#

clean:
	rm -f $(OBJ)

#___FCLEAN___#

fclean: clean
	rm -f $(NAME_NM)

#___RE___#

re: fclean all
