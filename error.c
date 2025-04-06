#include "so_long.h"

void	ft_print_errors(t_so_long *func)
{
	if (func->char_err == 1)
		printf("There is character rather than C 0 1 E P\n");
	if(func->exit_err == 1 || func->exit_err == 2)
		printf("There is no exit/ Too much exit point\n");
	if(func->start_err == 1 || func->start_err == 2)
		printf("There is no player/ Too much player\n");
	if(func->coll_err == 1)
		printf("There is no collectible\n");
	if(func->path_err == 1 || func->exit_err == 1 || func->start_err == 1) 
		printf("There is no valid path\n");
	if(func->wall_err == 1)
		printf("Walls are missing on the sides\n");
	if (func->exit_err == 1 || func->exit_err == 2 || func->start_err == 1 || func->start_err == 2
		|| func->coll_err == 1 || func->path_err == 1 || func->wall_err == 1 || func->char_err == 1)
		ft_error_map_game_exit(func, 1);
}
void ft_error_map_game_exit(t_so_long *func, int i)
{
	free_map(func);
	exit(i);
}
void	ft_error(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}
