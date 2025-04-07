/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aycami <aycami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 01:06:02 by aycami            #+#    #+#             */
/*   Updated: 2025/04/07 01:35:15 by aycami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	destroy_window(t_so_long *func)
{
	mlx_destroy_image(func->mlx, func->acorn);
	mlx_destroy_image(func->mlx, func->background);
	mlx_destroy_image(func->mlx, func->door);
	mlx_destroy_image(func->mlx, func->tree);
	mlx_destroy_image(func->mlx, func->totoro);
	mlx_destroy_image(func->mlx, func->totoro_with_door);
	mlx_destroy_window(func->mlx, func->win);
	mlx_destroy_display(func->mlx);
	ft_error_map_game_exit(func, 0);
	return (0);
}

void	check_on_exit(t_so_long *func, int i, int j)
{
	if (func->map[i][j] == 'E' && func->c_count == 0)
		destroy_window(func);
	if (func->map[i][j] == 'E')
	{
		func->map[func->player_i][func->player_j] = '0';
		func->map[i][j] = 'S';
	}
	else if (func->map[func->player_i][func->player_j] == 'S')
	{
		func->map[func->player_i][func->player_j] = 'E';
		func->map[i][j] = 'P';
	}
	else
	{
		func->map[func->player_i][func->player_j] = '0';
		func->map[i][j] = 'P';
	}
}

void	change_map(t_so_long *func, int i, int j)
{
	char	**map;

	map = func->map;
	if (map[i][j] == '0')
	{
		check_on_exit(func, i, j);
		func->player_i = i;
		func->player_j = j;
	}
	else if (map[i][j] == 'C')
	{
		check_on_exit(func, i, j);
		func->player_i = i;
		func->player_j = j;
		func->c_count--;
	}
	else if (map[i][j] == 'E')
	{
		check_on_exit(func, i, j);
		func->player_i = i;
		func->player_j = j;
	}
}

int	move_player(t_so_long *func, int i, int j)
{
	char	**map;
	int		p_i;
	int		p_j;

	map = func->map;
	p_i = func->player_i;
	p_j = func->player_j;
	if (map[p_i + i][p_j + j] == '1')
		return (0);
	else if (map[p_i + i][p_j + j] == '0' || map[p_i + i][p_j + j] == 'C' \
		|| map[p_i + i][p_j + j] == 'E')
	{
		change_map(func, p_i + i, p_j + j);
		image_to_map(func);
		return (1);
	}
	return (1);
}

int	key_press(int keycode, t_so_long *func)
{
	if (keycode == 65307)
	{
		printf("You lost! Moves: %d", func->moves++);
		destroy_window(func);
		exit(0);
	}
	else if ((keycode == 119 && move_player(func, -1, 0) == 1) || (keycode == 97
			&& move_player(func, 0, -1) == 1) || (keycode == 115
			&& move_player(func, 1, 0) == 1) || (keycode == 100
			&& move_player(func, 0, 1) == 1))
	{
		func->moves++;
		printf("moves: %d\n", func->moves);
	}
	return (0);
}
