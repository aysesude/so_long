/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aycami <aycami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 01:06:02 by aycami            #+#    #+#             */
/*   Updated: 2025/04/07 23:01:40 by aycami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	check_error_flag_empty_rec(t_so_long *func)
{
	if (func->empty_err == 1)
		ft_error("There is a empty line");
	if (func->rec_err == 1)
		ft_error("Not Rectangle / One line");
}

void	check_if_there_is_a_map(char **argv)
{
	int		fd;
	char	*line;
	int		flag;

	flag = 0;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (line)
			flag = 1;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (flag == 0)
		ft_error("There is a empty .ber file");
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
