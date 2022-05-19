# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 14:22:55 by bbordere          #+#    #+#              #
#    Updated: 2022/04/23 17:26:31 by bbordere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

INCLUDES = includes/

CFLAGS =  -I $(INCLUDES) -g3 -Wall -Wextra -Werror

FILES = pipex.c utils.c ft_strjoin.c ft_split.c get_next_line.c utils_ft.c data.c exec_pipeline.c here_doc.c

FILES_BONUS = pipex_bonus.c utils.c ft_strjoin.c ft_split.c get_next_line.c utils_ft.c data.c exec_pipeline.c here_doc.c

SRCS = $(addprefix src/, $(FILES))

SRCS_BONUS = $(addprefix src/, $(FILES_BONUS))

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

NAME = pipex
NAME_BONUS = pipex_bonus

%.o: %.c
	@printf "\033[0;33mCompiling : %-33.33s\r" $@
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@ printf '\n\033[0;33mCompiling pipex\033[0m\n'
	@ $(CC) $(CFLAGS) $(OBJS) -o $(NAME) 
	@ printf '\033[0;32mpipex compiled sucessfully !\033[0m\n'

all: $(NAME)

clean:
	@ rm -f $(OBJS)
	@ rm -f $(OBJS_BONUS)
	@ printf '\033[0;32mclean done\033[0m\n'

fclean: clean
	@ rm -f $(NAME)
	@ rm -f $(NAME_BONUS)
	@ printf '\033[0;32mfclean done\033[0m\n'

bonus: $(OBJS_BONUS)
	@ printf '\n\033[0;33mCompiling pipex_bonus\033[0m\n'
	@ $(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)
	@ printf '\033[0;32mpipex_bonus compiled sucessfully !\033[0m\n'

re: fclean all

.PHONY: all clean fclean re
 
.SILENT: $(OBJS) $(OBJS_BONUS)
