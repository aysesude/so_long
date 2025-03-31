#include "so_long.h"
int	destroy_window(t_so_long *func)
{
	int	i;

	i = 0;
	while (i < func->total_rows)
	{
		free(func->map[i]);
		i++;
	}
	free(func->map);
	mlx_destroy_image(func->mlx, func->acorn);
	mlx_destroy_image(func->mlx, func->background);
	mlx_destroy_image(func->mlx, func->door);
	mlx_destroy_image(func->mlx, func->tree);
	mlx_destroy_image(func->mlx, func->totoro);
	mlx_destroy_window(func->mlx, func->win);
	mlx_destroy_display(func->mlx);
	free(func->mlx);
	exit(0);
}

void change_map(t_so_long *func, int i, int j, char c)
{
	char	**map;
	int		p_i;
	int		p_j;

	p_i = 0;
	p_j = 0;
	if (c == '0')
		map[p_i][p_j] =
}

void	move_player(t_so_long *func, int i, int j)
{
	char **map;
	int p_i;
	int p_j;

	map = func->map;
	p_i = func->player_i;
	p_j = func->player_j;
	if (map[p_i + i][p_j + j] == '1')
		return (0);
	else if (map[p_i + i][p_j + j] == '0')
		change_map(func, p_i + i, p_i + j,'0');


}
int	key_press(int keycode, t_so_long *func)
{
	if (keycode == 65307)
	{
		printf("You lost! Moves:");
		destroy_window(func);
		exit(0);
	}
	else if ((keycode == 119 && move_player(func, -1, 0) == 1) || (keycode == 97
			&& move_player(func, 0, -1) == 1) || (keycode == 115
			&& move_player(func, 1, 0) == 1) || (keycode == 100 && move_player(func,
				0, 1) == 1))
	{
		func->moves++;
		printf("moves: %d\n", func->moves);
	}
	return (0);
}
void image_to_map(t_so_long *func)
{
	int i = 0;
	int j = 0;
	mlx_put_image_to_window(func->mlx, func->win, func->totoro,
		func->player_j * 64, func->player_i * 64);
	mlx_put_image_to_window(func->mlx, func->win, func->door,
		func->door_j * 64, func->door_i * 64);
		while (i < func->total_rows)
		{
			j = 0;
			while (func->map[i][j])
			{
				if (func->map[i][j] == '1')
					mlx_put_image_to_window(func->mlx, func->win, func->tree,
						j * 64, i * 64);
				else if (func->map[i][j] == '0')
					mlx_put_image_to_window(func->mlx, func->win, func->background,
						j * 64, i * 64);
				else if (func->map[i][j] == 'C')
					mlx_put_image_to_window(func->mlx, func->win, func->acorn,
						j * 64, i * 64);
				j++;
			}
			i++;
		}
}
void	ft_game_function(t_so_long *func)
{
	func->mlx = mlx_init();
	func->win = mlx_new_window(func->mlx, (func->row_length * 64),
			(func->total_rows * 64), "Asude");
	xpm_to_image(func);
	image_to_map(func);
	mlx_hook(func->win, 17, 1L << 17, destroy_window, func);
	mlx_hook(func->win, 2, 1L << 0, key_press, func);
	mlx_loop(func->mlx);
}

void xpm_to_image(t_so_long *func)
{
	int	i;
	int	j;

	i = 64;
	j = 64;

	func->background = mlx_xpm_file_to_image(func->mlx,
			"./textures/background.xpm", &i, &j);
	func->door = mlx_xpm_file_to_image(func->mlx,
			"./textures/door.xpm", &i, &j);
	func->acorn = mlx_xpm_file_to_image(func->mlx,
			"./textures/acorn.xpm", &i, &j);
	func->tree = mlx_xpm_file_to_image(func->mlx,
			"./textures/tree.xpm", &i, &j);
	func->totoro = mlx_xpm_file_to_image(func->mlx,
			"./textures/totoro.xpm", &i, &j);
}

void check_file_name(char **argv)
{
	int	i;

	i = 0;
	while(argv[1][i])
	{
		i++;
	}
	i--;
	printf("%d", i);
	if(argv[1][i] != 'r' || argv[1][i - 1] != 'e'
		|| argv[1][i - 2] != 'b' || argv[1][i - 3] != '.')
			ft_error("File is not .ber!");
}

int main(int argc, char **argv)
{
	t_so_long	func;
	int			i;

	ft_zero(&func);
	if (argc != 2)
	{
		write(2, "Usage: ./so_long map.ber\n", 26);
		return (1);
	}
	check_file_name(argv); //hatalıysa çıkış var
	check_emptyline_and_rectangle(argv); //hatalıysa çıkış var
	read_map(argv[1], &func);
	check_map_char(&func);
	check_char_count(&func);
	find_player_position(&func);
	find_door_position(&func);
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
