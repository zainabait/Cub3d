CC 						= cc 
MLX_REPO        		= https://github.com/codam-coding-college/MLX42
MLX_DIR         		= ./MLX42
MLX_BUILD_DIR   		= $(MLX_DIR)/build
MLX_LIB         		= $(MLX_BUILD_DIR)/libmlx42.a
MLX_FLAGS               = -L$(MLX_BUILD_DIR) -lmlx42 -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -lm
FLAGS                   = -Wall -Wextra -Werror -g -fsanitize=address
NAME					= cub3D
SRCS					= ./mandatory/parsing/get_next_line.c ./mandatory/parsing/get_next_line_utils.c \
						./mandatory/parsing/parsing_read_map.c main.c ./mandatory/parsing/parsing_helpe1.c ./mandatory/parsing/parsing_helpe2.c \
						./mandatory/parsing/parsing_map.c ./mandatory/parsing/parsing_map1.c ./mandatory/parsing/parsing_map2.c \
						./mandatory/parsing/parsing_map3.c ./mandatory/parsing/parsing_helpe3.c ./mandatory/parsing/mohilloc.c
OBJS					= $(SRCS:.c=.o)

all                     : $(NAME)

%.o                      : %.c cub.h
	@echo "\033[0;34mCompiling $<.\033[0;m"
	$(CC) $(FLAGS) -c $< -o $@

$(NAME)                 : $(MLX_LIB) 
						$(OBJS) $(CC) $(FLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS) 
$(NAME)                 : $(OBJS) 
						$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(MLX_LIB):
	if [ ! -d "$(MLX_DIR)" ]; then git clone $(MLX_REPO); fi
	cd $(MLX_DIR) && cmake -B build && make -C build
clean                   :
	@echo "\033[0;31mRemoving object files.\033[0;m"
	rm -f $(OBJS)
	@echo "\033[1;32mCleaning DONE ✅\033[0;m"


COL_CUBE   = \033[1;36m
COL_TITLE  = \033[1;35m
COL_TXT    = \033[1;37m
COL_SHADOW = \033[1;30m

launch:
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
	rm -f $(NAME) $(MLX_LIB)
	@echo "\033[1;32mCleaning DONE ✅\033[0;m"

re                      : fclean all
.PHONY					: clean 
