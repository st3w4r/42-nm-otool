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

SRC_NM =	nm.c \
			utils_file.c \
			utils_memory.c \
			display_common_symbol.c \
			display_common_section.c \
			display_common_hexa.c \
			display_nm.c \
			format_information_1.c \
			format_information_2.c \
			format_information_3.c \
			format_information_ar_1.c \
			format_information_ar_2.c \
			format_information_ar_3.c \
			format_information_symbol.c \
			handler.c \
			init_format.c \
			section_list.c \
			symbol_list.c \
			ft_puthexa_size.c \
			ft_print_mem.c \
			swap.c \
			init_file.c \
			archive_list.c \
			checker.c

SRC_OTOOL =	otool.c \
			utils_file.c \
			utils_memory.c \
			display_common_symbol.c \
			display_common_section.c \
			display_common_hexa.c \
			display_otool.c \
			format_information_1.c \
			format_information_2.c \
			format_information_3.c \
			format_information_ar_1.c \
			format_information_ar_2.c \
			format_information_ar_3.c \
			format_information_symbol.c \
			handler.c \
			init_format.c \
			section_list.c \
			symbol_list.c \
			ft_puthexa_size.c \
			ft_print_mem.c \
			swap.c \
			init_file.c \
			archive_list.c \
			checker.c


OBJ_NM = $(addprefix $(PATH_SRC), $(SRC_NM:.c=.o))
OBJ_OTOOL = $(addprefix $(PATH_SRC), $(SRC_OTOOL:.c=.o))

#____________RULES____________#

.PHONY: clean fclean re

all: $(NAME_NM) $(NAME_OTOOL)

$(NAME_NM): $(OBJ_NM)
	make -C libft/
	$(CC) $(OBJ_NM) -o $(NAME_NM) $(LIBS)

$(NAME_OTOOL): $(OBJ_OTOOL)
	make -C libft/
	$(CC) $(OBJ_OTOOL) -o $(NAME_OTOOL) $(LIBS)


#___CLEAN___#

clean:
	rm -f $(OBJ_NM)
	rm -f $(OBJ_OTOOL)

#___FCLEAN___#

fclean: clean
	rm -f $(NAME_NM)
	rm -f $(NAME_OTOOL)

#___RE___#

re: fclean all
