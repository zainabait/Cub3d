# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/29 17:47:21 by zait-bel          #+#    #+#              #
#    Updated: 2024/10/04 16:38:09 by zait-bel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror -Imlx -fsanitize=address -g

SRC = cub3d.c
BNS = ./bonus/ft_check_map_bonus.c ./bonus/ft_check_path_bonus.c ./bonus/ft_split_bonus.c ./bonus/get_next_line_utils_bonus.c ./bonus/get_next_line_bonus.c ./bonus/my_utils_bonus.c ./bonus/so_long_bonus.c ./bonus/ft_draw_map_bonus.c ./bonus/draw_utils_bonus.c ./bonus/draw_anim_bonus.c

OBJS = $(SRC:.c=.o)
OBJB = $(BNS:.c=.o)

NAME = cub3D
BONUS_NAME = cub3D_bonus

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -framework OpenGL -framework AppKit libmlx42.a -Iinclude -lglfw -L"$(shell brew --prefix glfw)/lib" $(OBJS) -o $(NAME)

bonus : $(OBJB)
	$(CC) $(CFLAGS) libmlx42.a -Iinclude -lglfwt $(OBJB) -o $(BONUS_NAME)

./mandatory/%.o: ./mandatory/%.c ./mandatory/cub3D.h
	$(CC) $(CFLAGS) -c $< -o $@

./bonus/%.o: ./bonus/%.c ./bonus/cub3D_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJB)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re:	fclean all

.PHONY: clean 