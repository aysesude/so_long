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
	int	exit_err;
	int	start_err;
	int	coll_err;
	int	path_err;
	int c_err;
	int p_err;
	int e_err;

	//OTHERS
	int		total_rows;
	int		row_length;
	char	**map;
	char	**path_map;
	int		c_count;
	int		p_count;
	int		e_count;
	int		player_i;
	int		player_j;
} t_so_long;

void	ft_error(char *msg);
void	ft_print_errors(t_so_long *func);


#endif
