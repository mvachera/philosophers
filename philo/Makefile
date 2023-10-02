# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/14 19:13:49 by mvachera          #+#    #+#              #
#    Updated: 2023/10/02 01:21:03 by mvachera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = philo

CC              = clang

CFLAGS  = -pthread -Wall -Wextra -Werror -g3 #-fsanitize=thread

RM              = rm -f

SRC     = srcs/main.c srcs/initialisation.c srcs/arg.c srcs/routine.c srcs/utils.c srcs/surveillance.c

OBJ	= ${SRC:.c=.o}

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean :
	${RM} ${OBJ}

fclean : clean
	${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re
