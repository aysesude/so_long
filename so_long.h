#ifndef SO_LONG_H
# define SO_LONG_H
#include "./get_next_line/get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct s_so_long
{
	//ERRORS
	int	empty_line_err;
	int	rectangle_err;
	int	exit_err;
	int	start_err;
	int	coll_err;
	int	path_err;

	//OTHERS
	int		total_rows;
	char	**map;
	char	**path_map;
} t_so_long;

void	ft_error(char *msg);
void	ft_print_errors(t_so_long *func);


#endif
