# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/13 11:54:09 by zait-bel          #+#    #+#              #
#    Updated: 2024/10/13 15:43:37 by zait-bel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 						= cc 
FLAGS                   = -Wall -Wextra -Werror -Imlx -fsanitize=address -g
NAME					= cub3D
NAME_BONUS			    = cub3D_bonus

SRCS					= ./mandatory/raycasting/cub3d.c \
						  ./mandatory/raycasting/player.c \
						  ./mandatory/raycasting/raycasting.c \
						  ./mandatory/raycasting/render.c \
						  ./mandatory/raycasting/utils.c \
						  ./mandatory/parsing/get_next_line.c \
						  ./mandatory/parsing/get_next_line_utils.c \
                          ./mandatory/parsing/parsing_read_map.c \
                          ./mandatory/parsing/ft_pars.c \
                          ./mandatory/parsing/parsing_helpe1.c \
                          ./mandatory/parsing/parsing_helpe2.c \
                          ./mandatory/parsing/parsing_map.c \
                          ./mandatory/parsing/parsing_map1.c \
                          ./mandatory/parsing/parsing_map2.c \
						  ./mandatory/parsing/parsing_map3.c \
						  ./mandatory/parsing/parsing_helpe3.c \
						  ./mandatory/parsing/mohilloc.c 
OBJS					= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[1;32mLinking $(NAME)...\033[0;m"
	$(CC) $(FLAGS) -framework OpenGL -framework AppKit libmlx42.a -Iinclude -lglfw -L"$(shell brew --prefix glfw)/lib" $(OBJS) -o $(NAME)

%.o: %.c
	@echo "\033[0;34mCompiling $<...\033[0;m"
	$(CC) $(FLAGS) -c $< -o $@

clean                   :
						 @echo "\033[0;31mRemoving object files.\033[0;m"
						 rm -f $(OBJS)
						 @echo "\033[1;32mCleaning DONE ✅\033[0;m"


COL_CUBE   = \033[1;36m
COL_TITLE  = \033[1;35m
COL_TXT    = \033[1;37m
COL_SHADOW = \033[1;30m

launch					:
						 clear
						 @echo "$(COL_CUBE)  .–––––––––––––––––––––––––––––––––––––––––––––––––––––––––.	"
						 @echo " / |$(COL_TITLE)           Loading textures, maps, and magic..$(COL_CUBE)          | \	"
						 @echo "+––+––––––––––––––––––––––––––––––––––––––––––––––––––––––––+––+"
						 @echo "|  |$(COL_TXT)             _____       _       _____ ____$(COL_CUBE)             |  |"
						 @echo "|  |$(COL_TXT)            /  __ \     | |     |____ |  _  \ $(COL_CUBE)          |  |"
						 @echo "|  |$(COL_TXT)           |  /  \/_   _| |__       / / | | |$(COL_CUBE)           |  |"
						 @echo "|  |$(COL_TXT)           |  |   | | | | |_ \      \ \ | | |$(COL_CUBE)           |  |"
						 @echo "|  |$(COL_TXT)           |  \__/\ |_| | |_) | ____/ / |_/ /$(COL_CUBE)           |  |"
						 @echo "|  |____________$(COL_TXT)\_____/\____|____/  \____/|____/ $(COL_CUBE)___________|  |"
						 @echo "| / $(COL_SHADOW)           /////// /////////     \\\\\\\\\\\\\\\\\\\ \\\\\\\\\\\\\\\\\\\\\\\\$(COL_CUBE)            \ |"
						 @echo "+––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––+\033[0m"
						 @echo "$(COL_TITLE)by: $(COL_CUBE)zait-bel                   $(COL_TITLE)   &&                      $(COL_CUBE)mohimi"	
fclean                  : clean
						 @echo "\033[0;31mRemoving object files.\033[0;m"
						 rm -f $(NAME)
						 @echo "\033[1;32mCleaning DONE ✅\033[0;m"

re                      : fclean all
.PHONY					: clean 
