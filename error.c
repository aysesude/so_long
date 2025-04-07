/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aycami" <aycami@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 01:06:02 by aycami            #+#    #+#             */
/*   Updated: 2025/04/07 08:04:51 by aycami"          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_so_long *func)
{
	int	i;

	if (func->map)
	{
		i = 0;
		while (func->map[i])
		{
			free(func->map[i]);
			i++;
		}
		free(func->map);
	}
	if (func->path_map)
	{
		i = 0;
		while (func->path_map[i])
		{
			free(func->path_map[i]);
			i++;
		}
		free(func->path_map);
	}
}

void	ft_print_errors(t_so_long *func)
{
	if (func->char_err == 1)
		write(2, "There is character rather than C 0 1 E P\n", 41);
	if (func->exit_err == 1 || func->exit_err == 2)
		write(2, "There is no exit/ Too much exit point\n", 38);
	if (func->start_err == 1 || func->start_err == 2)
		write(2, "There is no player/ Too much player\n", 36);
	if (func->coll_err == 1)
		write(2, "There is no collectible\n", 24);
	if (func->path_err == 1 || func->exit_err == 1 || func->start_err == 1)
		write(2, "There is no valid path\n", 23);
	if (func->wall_err == 1)
		write(2, "Walls are missing on the sides\n", 31);
	if (func->exit_err == 1 || func->exit_err == 2 || func->start_err == 1
		|| func->start_err == 2 || func->coll_err == 1 || func->path_err == 1
		|| func->wall_err == 1 || func->char_err == 1)
		ft_error_map_game_exit(func, 1);
}

void	ft_error_map_game_exit(t_so_long *func, int i)
{
	free_map(func);
	exit(i);
}

void	ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}
