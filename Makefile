NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = 	get_next_line_utils.c \
		get_next_line.c \
		so_long.c \
		check_map.c \
		read_map.c \
		error.c \
		find_pos.c \
		game_one.c \
		game_two.c

all: $(NAME)

$(NAME): ${SRCS}
	@make -C ./minilibx-linux
	@make -C ./ft_printf
	@$(CC) $(SRCS) $(CFLAGS) ./minilibx-linux/libmlx.a ./ft_printf/libftprintf.a -lX11 -lXext -lm -o $(NAME)
	@clear
	@echo "The make is done"
clean:
	@rm -rf $(NAME)
	@make clean -C minilibx-linux/
	@make clean -C ft_printf
fclean: clean
	@rm -rf $(NAME)
	@make clean -C minilibx-linux/
	@make fclean -C ft_printf
re: fclean all
