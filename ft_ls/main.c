#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "ft_ls.h"

#include <libft.h>

#include <math.h> // Add to libft

void	print_dirs_reverse(t_file *file)
{
	if (!file)
		return ;
	print_dirs_reverse(file->next);
	if (file->name)
		ft_printf("%s\n", file->name);
}

void	print_dirs(t_all *lst)
{
	if (lst->options == 0)
		while (lst->file->next)
		{
			ft_printf("%s\n", lst->file->name);
			lst->file = lst->file->next;
		}
		else if (lst->options == 16)
			print_dirs_reverse(lst->file);
}

void	get_dirs(t_all *lst)
{
	void			*dir;
	struct dirent	*rdir;

	t_file			*head;

	lst->file = (t_file *)ft_memalloc(sizeof(t_file));
	head = lst->file;

	dir = opendir(".");
	if (dir != NULL)
	{
		while ((rdir = readdir(dir)) != NULL)
		{
			if (lst->options != 2 && *rdir->d_name != '.') //change to bitwise
			{
				head->name = rdir->d_name;
				head->next = (t_file *)ft_memalloc(sizeof(t_file));
				head = head->next;
			}
		}
	}
}

void	get_options(t_all *lst, char *args[])
{
	while (*args)
	{
		if (ft_strcmp(*args, "-a") == 0)
			lst->options += 2;
		if (ft_strcmp(*args, "-l") == 0)
			lst->options += pow(2, 2);
		if (ft_strcmp(*args, "-R") == 0)
			lst->options += pow(2, 3);
		if (ft_strcmp(*args, "-r") == 0)
			lst->options += pow(2, 4);
		if (ft_strcmp(*args, "-t") == 0)
			lst->options += pow(2, 5);
		args++;
	}
}

int		main(int argc, char *argv[])
{
	t_all	*lst;

	lst = (t_all *)ft_memalloc(sizeof(t_all));
	if (argc > 1)
		get_options(lst, argv);
	get_dirs(lst);
	print_dirs(lst);
}