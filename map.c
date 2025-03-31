#include "so_long.h"

void	free_map(t_so_long *func)
{
	int i;

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

void	count_lines(char *filename, t_so_long *func)
{
	int fd;
	int count;
	char *line;

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
			if(line[0] == '\n')
				count--;
		}
		if(line)
			count++;
	}
	free(line);
	close(fd);
	func->total_rows = count;
	printf("row_length: %d \ntotal_rows: %d\n", func->row_length, func->total_rows);
}

void	read_map(char *filename, t_so_long *func)
{
	int fd;
	char *line;
	int	i;
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
		free(func->map);
		free(func->path_map);
		ft_error("File open error");
	}
	i = 0;
	while (i < func->total_rows)
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
		free(line);
		i++;
	}
	func->map[i] = NULL;
	func->path_map[i] = NULL;
	close(fd);
	// return (func->map);
}

void	ft_zero(t_so_long *func)
{
	//ERRORS
	func->exit_err = 0;
	func->start_err = 0;
	func->coll_err = 0;
	func->path_err = 0;
	func->wall_err = 0;

	//OTHERS
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
void	check_map_char(t_so_long *func)
{
	int	i;
	int	j;
	char **map;

	i = 0;
	j = 0;
	if (!func->map)
    	ft_error("Map is not initialized properly.");
	map = func->map;
	while (i < func->total_rows)
	{
		j = 0;
		while(func->map[i][j])
		{
			if (map[i][j] != 'C' && map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'E'
				&& map[i][j] != 'P')
					ft_error("There is character rather than C 0 1 E P");
			if(map[i][j] == 'E')
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
	int	i;
	int	j;
	char **map;

	i = 0;
	j = 0;
	map = func->map;

	while (i < func->total_rows)
	{
		j = 0;
		while(map[i][j])
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
	printf("door position player[%d][%d]\n", func->door_i, func->door_j);
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
	printf("player position player[%d][%d]\n", func->player_i, func->player_j);
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
			if(((int)ft_strlen(line) + 1 ) != tmp)
				ft_error("Not rectangle");
		}
		else if((int)ft_strlen(line) != tmp)
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
	while(i < func->row_length)
	{
		if(func->map[0][i] != '1' || func->map[func->total_rows - 1][i] != '1')
		{
			ft_error("Wall error");
			func->wall_err = 1;
		}
		i++;
	}
	i = 0;
	while(i < func->total_rows)
	{
		if(func->map[i][func->row_length - 1] != '1' || func->map[i][0] != '1')
		{
			ft_error("Wall error");
			func->wall_err = 1;
		}
		i++;
	}
}

void	check_valid_path(t_so_long *func, int i, int j)
{
	if (i < 0 || j < 0 || i >= func->total_rows || j >= func->row_length)
		return; // Harita dışına çıkmayı engelle
	if(i < func->total_rows && j < func->row_length)
	{
		// printf("Bakılan yer: %d %d \n", i, j);
		if(func->path_map[i][j] != '1' && func->path_map[i][j] != '.')
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
	while(i < func->total_rows)
	{
		j = 0;
		while(j < func->row_length)
		{
			if(func->path_map[i][j] == 'E' || func->path_map[i][j] == 'C')
				ft_error("There is no valid path");
			j++;
		}
		i++;
	}
}
