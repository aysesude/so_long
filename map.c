#include "so_long.h"

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
	func->row_length = ft_strlen(line) - 1;
	while (line)
	{
		line = get_next_line(fd);
		if (line)
		{
			if(line[0] == '\n')
				count--;
		}
		if(line)
			count++;
		free(line);
	}
	close(fd);
	func->total_rows = count;
	printf("%d %d\n", func->row_length, func->total_rows);
}

char **read_map(char *filename, t_so_long *func)
{
	int fd;
	char *line;
	int	i;
	i = 0;

	count_lines(filename, func);
	if (func->total_rows <= 0)
		return (NULL);
	func->map = (char **)malloc(sizeof(char *) * (func->total_rows + 1));
	func->path_map = (char **)malloc(sizeof(char *) * (func->total_rows + 1));
	if (!func->map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(func->map);
		return (NULL);
	}
	i = 0;
	// printf("func %d", func->total_rows);
	while (i < func->total_rows)
	{
		line = get_next_line(fd);
		// printf("line %s\n", line);
		if (line)
			line[(func->row_length)] = '\0';
		func->map[i] = line;
		i++;
	}
	func->map[i] = NULL;
	close(fd);
	return (func->map);
}

void	ft_zero(t_so_long *func)
{
	//ERRORS
	func->exit_err = 0;
	func->start_err = 0;
	func->coll_err = 0;
	func->path_err = 0;
	func->c_err = 0;
	func->e_err = 0;
	func->p_err = 0;

	//OTHERS
	func->total_rows = 0;
	func->map = NULL;
	func->c_count = 0;
	func->e_count = 0;
	func->p_count = 0;
	func->player_i = 0;
	func->player_j = 0;
	
}
void	check_map_char(t_so_long *func)
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
			if (map[i][j] != 'C' && map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'E'
				&& map[i][j] != 'P')
					ft_error("There is character rather than C 0 1 E P");
			j++;
		}
		i++;
	}
}
void error_char_count(t_so_long *func)
{
	if (func->c_count == 0)
	{
		func->c_err = 1;
		ft_error("There is no collectable in map\n");
	}
	if (func->p_count == 0)
	{
		func->p_err = 1;
		ft_error("There is no player in map\n");
	}
	if (func->p_count > 1)
	{
		func->p_err = 2;
		ft_error("There is more than one  player in map\n");
	}
	if (func->e_count == 0)
	{
		func->e_err = 1;
		ft_error("There is no exit in map\n");
	}
	if (func->e_count > 1)
	{
		func->e_err = 2;
		ft_error("There is more than one  exit in map\n");
	}
}
void check_char_count(t_so_long *func)
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
void find_player_position(t_so_long *func)
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

// void check_valid_path(t_so_long *func, int i, int j)
// {
// 	char **map;
// 	map = func->path_map;

// 	if (map[i][j] != 'C')
		
// }

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
		printf("rectangle %s",line);
		if(line[0] == '\n')
			ft_error("Empty line error");
		if((int)ft_strlen(line) != tmp)
			ft_error("Not rectangle");
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

int main(int argc, char **argv)
{
	t_so_long	func;
	int			i;

	ft_zero(&func);
	if (argc != 2)
	{
		write(2, "Usage: ./so_long map.ber\n", 31);
		return (1);
	}
	check_emptyline_and_rectangle(argv);
	func.map = read_map(argv[1], &func);
	check_map_char(&func);
	check_char_count(&func);
	find_player_position(&func);
	// check_valid_path(&func, func.player_i, func.player_j);
	if (!func.map)
		return (1);
	i = 0;
	while (func.map[i])
	{
		// write(1, func.map[i], strlen(func.map[i]));
		free(func.map[i]);
		i++;
	}
	ft_print_errors(&func);
	free(func.map);
	return (0);
}
