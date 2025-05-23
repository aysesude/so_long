/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aycami" <aycami@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 01:06:02 by aycami            #+#    #+#             */
/*   Updated: 2025/04/07 09:09:28 by aycami"          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map_char(t_so_long *func)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!func->map)
		ft_error("Map is not initialized properly.");
	while (i < func->total_rows)
	{
		j = 0;
		while (func->map[i][j])
		{
			if (func->map[i][j] != 'C' && func->map[i][j] != '0' &&
				func->map[i][j] != '1' && func->map[i][j] != 'E' &&
				func->map[i][j] != 'P')
				func->char_err = 1;
			if (func->map[i][j] == 'E')
			{
				func->exit_i = i;
				func->exit_j = j;
			}
			j++;
		}
		i++;
	}
}

void	error_char_count(t_so_long *func)
{
	if (func->c_count == 0)
		func->coll_err = 1;
	if (func->p_count == 0)
		func->start_err = 1;
	if (func->p_count > 1)
		func->start_err = 2;
	if (func->e_count == 0)
		func->exit_err = 1;
	if (func->e_count > 1)
		func->exit_err = 2;
}

void	check_char_count(t_so_long *func)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	j = 0;
	map = func->map;
	while (i < func->total_rows)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				func->c_count++;
			if (map[i][j] == 'E')
				func->e_count++;
			if (map[i][j] == 'P')
				func->p_count++;
			j++;
		}
		i++;
	}
	error_char_count(func);
}

void	check_valid_path(t_so_long *func, int i, int j)
{
	if (i < 0 || j < 0 || i >= func->total_rows || j >= func->row_length)
		return ;
	if (i < func->total_rows && j < func->row_length)
	{
		if (func->path_map[i][j] != '1' && func->path_map[i][j] != '.')
		{
			func->path_map[i][j] = '.';
			check_valid_path(func, (i + 1), j);
			check_valid_path(func, i, j + 1);
			check_valid_path(func, i - 1, j);
			check_valid_path(func, i, j - 1);
		}
	}
}

void	check_path(t_so_long *func)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	check_valid_path(func, func->player_i, func->player_j);
	while (i < func->total_rows)
	{
		j = 0;
		while (j < func->row_length)
		{
			if (func->path_map[i][j] == 'E' || func->path_map[i][j] == 'C')
				func->path_err = 1;
			j++;
		}
		i++;
	}
}
