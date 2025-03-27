#include "so_long.h"

void	ft_print_errors(t_so_long *func)
{
	//if(func->empty_line_err == 1)
	//	ft_error("Empty Line Error");
	//if(func->rectangle_err == 1)
	//	ft_error("Map is not rectanle");
	if(func->exit_err == 1)
		ft_error("There is no exit/ Too much exit point");
	if(func->start_err == 1)
		ft_error("There is no start/ Too much start point");
	if(func->coll_err == 1)
		ft_error("There is no collectible");
	if(func->path_err == 1)
		ft_error("There is no valid path");
	if(func->wall_err == 1)
		ft_error("Walls are missing on the sides");
}

void	ft_error(char *msg)
{
	printf("%s", msg);
	exit(1);
}
