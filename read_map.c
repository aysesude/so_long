/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aycami <aycami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 01:06:02 by aycami            #+#    #+#             */
/*   Updated: 2025/04/07 01:35:15 by aycami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_lines(char *filename, t_so_long *func)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error("fd error");
	count = 1;
	line = get_next_line(fd);
	if (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			func->row_length = ft_strlen(line) - 1;
		else
			func->row_length = ft_strlen(line);
	}
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line)
		{
			if (line[0] == '\n')
				count--;
		}
		if (line)
			count++;
	}
	free(line);
	close(fd);
	func->total_rows = count;
}

void	read_map(char *filename, t_so_long *func)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	count_lines(filename, func);
	if (func->total_rows <= 0)
		exit(0);
	func->map = (char **)malloc(sizeof(char *) * (func->total_rows + 1));
	func->path_map = (char **)malloc(sizeof(char *) * (func->total_rows + 1));
	if (!func->map || !func->path_map)
	{
		free(func->map);
		free(func->path_map);
		exit(0);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free_map(func);
		ft_error("File open error");
	}
	i = 0;
	while (i < func->total_rows + 1)
	{
		line = get_next_line(fd);
		if (line)
		{
			line[(func->row_length)] = '\0';
			func->map[i] = ft_strdup(line);
			func->path_map[i] = ft_strdup(line);
			if (!func->map[i] || !func->path_map[i])
				ft_error("Memory allocation error");
		}
		else
			break ;
		free (line);
		i++;
	}
	func->map[i] = NULL;
	func->path_map[i] = NULL;
	close(fd);
}
