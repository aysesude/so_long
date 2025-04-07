#include "so_long.h"

void	find_door_position(t_so_long *func)
{
	int	i;
	int	j;
	char **map;

	i = 0;
	j = 0;
	map = func->map;
	while (i < func->total_rows)
	{
		j = 0;
		while(func->map[i][j])
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
	// printf("door position player[%d][%d]\n", func->door_i, func->door_j);
}

void	find_player_position(t_so_long *func)
{
	int	i;
	int	j;
	char **map;

	i = 0;
	j = 0;
	map = func->map;
	while (i < func->total_rows)
	{
		j = 0;
		while(func->map[i][j])
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
	// printf("player position player[%d][%d]\n", func->player_i, func->player_j);
}