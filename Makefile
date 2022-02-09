# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 14:22:55 by bbordere          #+#    #+#              #
#    Updated: 2022/02/09 16:41:26 by bbordere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

INCLUDES = includes/

CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES)

FILES = pipex.c utils.c

FILES_BONUS = pipex_bonus.c utils.c

SRCS = $(addprefix src/, $(FILES))

SRCS_BONUS = $(addprefix src/, $(FILES_BONUS))

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

NAME = pipex

$(NAME): $(OBJS)

	@ printf '\033[0;33mCompiling Libft\033[0m\n'
	@ $(MAKE) -s all -C libft
	@ printf '\033[0;32mLibft compiled sucessfully !\033[0m\n'
	@ printf '\033[0;33mCompiling pipex\033[0m\n'
	@ ${CC} ${CFLAGS} $(OBJS) libft/libft.a -o ${NAME} 
	@ printf '\033[0;32mpipex compiled sucessfully !\033[0m\n'

all: $(NAME)

clean:
	@ rm -f $(OBJS)
	@ rm -f $(OBJS_BONUS)
	@ $(MAKE) -s clean -C libft
	@ printf '\033[0;32mclean done\033[0m\n'

fclean: clean
	@ rm -f ${NAME}
	@ $(MAKE) -s fclean -C libft
	@ printf '\033[0;32mfclean done\033[0m\n'

bonus: $(OBJS_BONUS)
	@ printf '\033[0;33mCompiling Libft\033[0m\n'
	@ $(MAKE) -s all -C libft
	@ printf '\033[0;32mLibft compiled sucessfully !\033[0m\n'
	@ printf '\033[0;33mCompiling pipex\033[0m\n'
	@ ${CC} ${CFLAGS} $(OBJS_BONUS) libft/libft.a -o ${NAME} 
	@ printf '\033[0;32mpipex compiled sucessfully !\033[0m\n'

re: fclean all

.PHONY: all clean fclean re
 
.SILENT: $(OBJS) $(OBJS_BONUS)
