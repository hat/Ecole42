
#include "ft_ls.h"

//PRINT ALL FILES FIRST AND THEN EVERYTHING ELSE WITH \n AND ALL
//STRUCT FOR FILE AND DIR?

//MAKE IT WHERE YOU GET THE STATS OF ALL THE FILES FIRST
//AND SAVE IT TO A STRUCT

/*
** check_bit
** Checks if a bit has been turned on
*/

int		check_bit(const int num, int byte)
{
	return ((num) & (1<<(byte)));
}

/*
** ls_files
** Gets all of the files that are pased in as args
** and sorts them accordingly
*/

int		ls_files(t_all *lst, t_file *file)
{
	int cur_dir;

	cur_dir = 0;
	while (cur_dir < lst->dirc)
	{
		file = get_all(lst, cur_dir);
		if (file->name != NULL && file->isFile)
		{
			bubblesort(file);
			check_print_dirs(lst, file, cur_dir);
		}
		cur_dir++;
	}
	return (cur_dir--);
}

/*
** ls_dirs
** Gets all of the files that are currently in the directory
** and sorts them accordingly
*/

void	ls_dirs(t_all *lst, t_file *file)
{
	int cur_dir;

	cur_dir = 0;
	while (cur_dir < lst->dirc)
	{
		file = get_all(lst, cur_dir);
		if (file->name != NULL && !file->isFile)
		{
			bubblesort(file);
			check_print_dirs(lst, file, cur_dir);
			if (lst->dirc > 1 && cur_dir + 1 != lst->dirc)
				ft_printf("\n");
		}
		cur_dir++;
	}
}

/*
**	Main function
**  calls upon other functions for ft_ls
*/

int		main(int argc, char *argv[])
{
	t_all	*lst;
	t_file	*file;

	lst = (t_all *)ft_memalloc(sizeof(t_all));
	lst->dirv = (char **)ft_memalloc(sizeof(char *) * argc);
	lst->dirv[0] = ft_strdup("./");
	lst->dirc = 1;
	get_dir(lst, argc, argv);
	if (lst->dirv)
	{
		bubblesort_dirs(lst);
		if (argc > 1)
			get_options(lst, argc, argv);
		file = get_all(lst, 0);
		if (ls_files(lst, file) < lst->dirc)
			ft_printf("\n");
		ls_dirs(lst, file);
	}
}
