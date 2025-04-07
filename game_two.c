#include "so_long.h"

void	put_others_to_window(t_so_long *func, int i, int j)
{
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
			else if (func->map[i][j] == 'S')
				mlx_put_image_to_window(func->mlx, func->win,
					func->totoro_with_door, j * 64, i * 64);
			j++;
		}
		i++;
	}
}

void	image_to_map(t_so_long *func)
{
	mlx_put_image_to_window(func->mlx, func->win, func->totoro,
		func->player_j * 64, func->player_i * 64);
	mlx_put_image_to_window(func->mlx, func->win, func->door,
		func->door_j * 64, func->door_i * 64);
	put_others_to_window(func, 0, 0);
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

void	xpm_to_image(t_so_long *func)
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
	func->totoro_with_door = mlx_xpm_file_to_image(func->mlx,
			"./textures/totoro_with_door.xpm", &i, &j);
}
