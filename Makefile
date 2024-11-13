# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 17:51:53 by mbudkevi          #+#    #+#              #
#    Updated: 2024/06/08 20:44:41 by mbudkevi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MY_SOURCES = so_long.c \
			helpers/line_length.c \
			helpers/map_length.c \
			helpers/find_position.c \
			helpers/find_element.c \
			helpers/find_exit.c \
			helpers/free_map.c \
			map_validation/is_playable.c \
			map_validation/is_rectangular.c \
			map_validation/is_closed.c \
			map_validation/is_valid_path.c \
			map_validation/is_valid.c \
			game_loop/start_game.c \
			game_loop/render_map.c \
			game_loop/key_handling.c \
			game_loop/exit_game.c \
			game_loop/display_moves.c

BONUS_SOURCES = bonus/bonus_so_long.c \
			bonus/helpers/line_length.c \
			bonus/helpers/map_length.c \
			bonus/helpers/find_position.c \
			bonus/helpers/find_element.c \
			bonus/helpers/find_exit.c \
			bonus/helpers/free_map.c \
			bonus/map_validation/is_playable.c \
			bonus/map_validation/is_rectangular.c \
			bonus/map_validation/is_closed.c \
			bonus/map_validation/is_valid_path.c \
			bonus/map_validation/is_valid.c \
			bonus/game_loop/start_game.c \
			bonus/game_loop/render_map.c \
			bonus/game_loop/key_handling.c \
			bonus/game_loop/exit_game.c \
			bonus/game_loop/display_moves.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

BONUS_OBJ = $(BONUS_SOURCES:.c=.o)

NAME = so_long

CC = cc

CFLAGS += -Wall -Werror -Wextra

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clone:
	if [ ! -d "minilibx" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git minilibx; \
	fi

$(NAME): clone $(MY_OBJECTS)
	make -C libftPrintfGnl
	make -C minilibx
	$(CC) $(CFLAGS) $(MY_OBJECTS) libftPrintfGnl/libft.a -Lminilibx -lmlx_Linux -lX11 -lXext -o $(NAME)

bonus: clone $(BONUS_OBJ)
	make -C libftPrintfGnl
	make -C minilibx
	$(CC) $(CFLAGS) $(BONUS_OBJ) libftPrintfGnl/libft.a -Lminilibx -lmlx_Linux -lX11 -lXext -o $(NAME)

clean:
	make clean -C libftPrintfGnl
	make clean -C minilibx
	rm -f $(MY_OBJECTS)
	rm -f $(BONUS_OBJ)

fclean: clean
	make fclean -C libftPrintfGnl
	rm -rf minilibx
	rm -f $(NAME)

re: fclean all	
	
