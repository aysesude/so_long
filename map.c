#include "so_long.h"

void	count_lines(char *filename, t_so_long *func)
{
	int fd;
	int count;
	char *line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error("fd error");
	count = 0;
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close(fd);
	func->total_rows = count;
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
	printf("func %d", func->total_rows);
	while (i < func->total_rows)
	{
		line = get_next_line(fd);
		func->map[i] = line;
		func->path_map[i] = line;
		i++;
	}
	func->map[i] = NULL;
	close(fd);
	return (func->map);
}

void	ft_zero(t_so_long *func)
{
	//ERRORS
	func->empty_line_err = 0;
	func->rectangle_err = 0;
	func->exit_err = 0;
	func->start_err = 0;
	func->coll_err = 0;
	func->path_err = 0;

	//OTHERS
	func->total_rows = 0;
	func->map = NULL;
}
void	check_walls(t_so_long *func)
{
	int	i;

	i = 0;
	while (i < func)
}

void	check_rectangle(t_so_long *func)
{
	int	i;
	int	tmp;

	i = 1;
	while(i < func->total_rows)
	{
		if (ft_strlen(func->map[i]) != ft_strlen(func->map[i - 1]))
			func->rectangle_err = 1;
		i++;
	}
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
	func.map = read_map(argv[1], &func);
	check_walls(&func);
	if (!func.map)
		return (1);
	i = 0;
	while (func.map[i])
	{
		write(1, func.map[i], strlen(func.map[i]));
		free(func.map[i]);
		i++;
	}
	ft_print_errors(&func);
	free(func.map);
	return (0);
}
