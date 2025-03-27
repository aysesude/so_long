#include "so_long.h"

void	ft_game_function(t_so_long *func)
{
	func->mlx = mlx_init();
	func->win = mlx_new_window(func->mlx, (func->row_length * 64),
			(func->total_rows * 64), "Asude");
	mlx_loop(func->mlx);
	xpm_to_image(func);
}

void xpm_to_image(t_so_long *func)
{
	int	i;
	int	j;

	i = 64;
	j = 64;

	func->background = mlx_xpm_file_to_image(func->mlx,
			"./textures/grass.xpm", &i, &j);
	func->door = mlx_xpm_file_to_image(func->mlx,
			"./textures/gate_xpm.xpm", &i, &j);
	func->acorn = mlx_xpm_file_to_image(func->mlx,
			"./textures/coin.xpm", &i, &j);
	func->tree = mlx_xpm_file_to_image(func->mlx,
			"./textures/wall.xpm", &i, &j);
	func->totoro = mlx_xpm_file_to_image(func->mlx,
			"./textures/ugly1.xpm", &i, &j);
}

int main(int argc, char **argv)
{
	t_so_long	func;
	int			i;

	ft_zero(&func);
	if (argc != 2)
	{
		write(2, "Usage: ./so_long map.ber\n", 31);
		return (1);
	}
	check_emptyline_and_rectangle(argv);
	read_map(argv[1], &func);
	check_map_char(&func);
	check_char_count(&func);
	find_player_position(&func);
	check_walls(&func);
	check_path(&func);
	ft_game_function(&func);
	i = 0;
	while (i < func.total_rows)
	{
		write(1, func.path_map[i], ft_strlen(func.path_map[i]));
		write(1, "\n", 1);
		free(func.path_map[i]);
		i++;
	}
	ft_print_errors(&func);
	free(func.map);
	return (0);
}
