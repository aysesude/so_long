#ifndef SO_LONG_H
# define SO_LONG_H
#include "./get_next_line/get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./minilibx-linux/mlx.h"

typedef struct s_so_long
{
	//ERRORS
	int	exit_err;
	int	start_err;
	int	coll_err;
	int	path_err;
	int	wall_err;
	int char_err;
	//MLX
	void	*mlx;
	void	*win;
	void	*background;
	void	*door;
	void	*acorn;
	void	*tree;
	void	*totoro;
	void	*totoro_with_door;
	//OTHERS
	int		door_i;
	int		door_j;
	int		total_rows;
	int		row_length;
	char	**map;
	char	**path_map;
	int		c_count;
	int		p_count;
	int		e_count;
	int		player_i;
	int		player_j;
	int		exit_i;
	int		exit_j;
	int		moves;

} t_so_long;

void	ft_error(char *msg);
void	ft_print_errors(t_so_long *func);
void ft_error_map_game_exit(t_so_long *func, int i);
void	check_file_name(char **argv);
void	count_lines(char *filename, t_so_long *func);
void	read_map(char *filename, t_so_long *func);
void	ft_zero(t_so_long *func);
void	check_map_char(t_so_long *func);
void	error_char_count(t_so_long *func);
void	check_char_count(t_so_long *func);
void	find_player_position(t_so_long *func);
void	check_emptyline_and_rectangle(char **argv);
void	check_walls(t_so_long *func);
void	check_valid_path(t_so_long *func, int x, int y);
void	check_path(t_so_long *func);
void	free_map(t_so_long *func);
void	find_door_position(t_so_long *func);
void 	xpm_to_image(t_so_long *func);
void 	image_to_map(t_so_long *func);
int		destroy_window(t_so_long *func);

#endif
