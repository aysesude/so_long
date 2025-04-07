/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aycami <aycami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 01:06:02 by aycami            #+#    #+#             */
/*   Updated: 2025/04/07 01:35:15 by aycami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_zero(t_so_long *func)
{
	func->exit_err = 0;
	func->start_err = 0;
	func->coll_err = 0;
	func->path_err = 0;
	func->wall_err = 0;
	func->char_err = 0;
	func->total_rows = 0;
	func->map = NULL;
	func->c_count = 0;
	func->e_count = 0;
	func->p_count = 0;
	func->player_i = 0;
	func->player_j = 0;
	func->door_i = 0;
	func->door_j = 0;
	func->moves = 0;
}

void	check_file_name(char **argv)
{
	int	i;

	i = 0;
	while (argv[1][i])
	{
		i++;
	}
	i--;
	if (argv[1][i] != 'r' || argv[1][i - 1] != 'e'
		|| argv[1][i - 2] != 'b' || argv[1][i - 3] != '.')
		ft_error("File is not .ber!");
}

void	check_emptyline_and_rectangle(char **argv)
{
	int		fd;
	int		tmp;
	char	*line;

	fd = open(argv[1], O_RDWR);
	if (fd == -1)
		ft_error("File error");
	line = get_next_line(fd);
	tmp = ft_strlen(line);
	while (line)
	{
		if (line[0] == '\n')
			ft_error("Empty line error");
		if (line[(int)ft_strlen(line) - 1] != '\n')
		{
			if (((int)ft_strlen(line) + 1) != tmp)
				ft_error("Not rectangle");
		}
		else if ((int)ft_strlen(line) != tmp)
			ft_error("Not rectangle");
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

void	check_walls(t_so_long *func)
{
	int	i;

	i = 0;
	while (i < func->row_length)
	{
		if (func->map[0][i] != '1' || func->map[func->total_rows - 1][i] != '1')
			func->wall_err = 1;
		i++;
	}
	i = 0;
	while (i < func->total_rows)
	{
		if (func->map[i][func->row_length - 1] != '1' || func->map[i][0] != '1')
			func->wall_err = 1;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_so_long	func;

	ft_zero(&func);
	if (argc != 2)
	{
		write(2, "Usage: ./so_long map.ber\n", 26);
		return (1);
	}
	check_file_name(argv);
	check_emptyline_and_rectangle(argv);
	read_map(argv[1], &func);
	check_map_char(&func);
	check_char_count(&func);
	find_player_position(&func);
	find_door_position(&func);
	check_walls(&func);
	check_path(&func);
	ft_print_errors(&func);
	ft_game_function(&func);
	return (0);
}
