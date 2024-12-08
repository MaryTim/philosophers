# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 17:51:53 by mbudkevi          #+#    #+#              #
#    Updated: 2024/12/03 12:31:58 by mbudkevi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MY_SOURCES = philo.c \
			utils/helpers.c \
			utils/input_validation.c \
			utils/init_utils.c \
			process_init.c \
			monitor.c \
			threads.c		

MY_OBJECTS = $(MY_SOURCES:.c=.o)

NAME = philo

CC = cc

CFLAGS += -Wall -Werror -Wextra

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(MY_OBJECTS)
	$(CC) $(CFLAGS) $(MY_OBJECTS) -o $(NAME)

clean:
	rm -f $(MY_OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all	
	
