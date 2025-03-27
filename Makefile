NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -Lmlx -lmlx -framework OpenGL -framework AppKit -fsanitize=address -g
SRCS = ./get_next_line/get_next_line_utils.c \
		./get_next_line/get_next_line.c \
		so_long.c \
		map.c \
		error.c \

all: $(NAME)

$(NAME): ${SRCS}
	@make -C ./mlx
	@$(CC) $(SRCS) $(CFLAGS) -o $(NAME)
	@clear
	@echo "The make is done"
clean:
	@rm -rf $(NAME)
	#@make clean -C mlx/
fclean: clean
	@rm -rf $(NAME)
	@make clean -C mlx/
re: fclean all
