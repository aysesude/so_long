/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aycami <aycami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 01:06:02 by aycami            #+#    #+#             */
/*   Updated: 2025/04/07 01:35:15 by aycami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_door_position(t_so_long *func)
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
		while (func->map[i][j])
		{
			if (map[i][j] == 'E')
			{
				func->door_i = i;
				func->door_j = j;
			}
			j++;
		}
		i++;
	}
}

void	find_player_position(t_so_long *func)
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
		while (func->map[i][j])
		{
			if (map[i][j] == 'P')
			{
				func->player_i = i;
				func->player_j = j;
			}
			j++;
		}
		i++;
	}
}
