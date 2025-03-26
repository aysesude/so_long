NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
SRCS = ./get_next_line/get_next_line_utils.c \
		./get_next_line/get_next_line.c \
		map.c \
		error.c \

all: $(NAME)

$(NAME): ${SRCS}
	#@make -C ./mlx
	@$(CC) $(SRCS) $(CFLAGS) -o $(NAME)
	@clear
	@echo "The make is done"
clean:
	@rm -rf $(NAME)
	#@make clean -C mlx/
fclean: clean
	@rm -rf $(NAME)
	#@make clean -C mlx/
re: fclean all
