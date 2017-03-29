
#include "ft_ls.h"

//PRINT ALL FILES FIRST AND THEN EVERYTHING ELSE WITH \n AND ALL
//STRUCT FOR FILE AND DIR?

int		check_bit(const int num, int byte)
{
	return ((num) & (1<<(byte)));
}

int		main(int argc, char *argv[])
{
	t_all	*lst;
	t_file	*file;
	int		cur_dir;

	lst = (t_all *)ft_memalloc(sizeof(t_all));
	lst->dirv = (char **)ft_memalloc(sizeof(char *) * argc);
	lst->dirv[0] = ft_strdup("./");
	lst->dirc = 1;
	cur_dir = 0;
	get_dir(lst, argc, argv);
	bubblesort_dirs(lst);
	if (argc > 1)
		get_options(lst, argc, argv);
	while (cur_dir < lst->dirc)
	{
		file = get_all(lst, cur_dir);
		if (file->name != NULL)
		{
			bubblesort(file);
			check_print_dirs(lst, file, cur_dir);
		}
		// if (lst->dirc > 1 && cur_dir + 1 != lst->dirc)
		// 	ft_printf("\n");
		cur_dir++;
	}
}