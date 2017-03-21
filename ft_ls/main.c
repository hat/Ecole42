#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "ft_ls.h"

#include <libft.h>

#include <math.h> // Add to libft

int		check_bit(const int num, int byte)
{
	return ((num) & (1<<(byte)));
}

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
	if ( !(check_bit(lst->options, 4)) )
		while (lst->file->next)
		{
			ft_printf("%s\n", lst->file->name);
			lst->file = lst->file->next;
		}
	else
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
			if ( !(check_bit(lst->options, 1)) ) //change to bitwise
			{
				if (* rdir->d_name != '.')
				{
					head->name = rdir->d_name;
					head->next = (t_file *)ft_memalloc(sizeof(t_file));
					head = head->next;
				}
			}
			else
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
	lst->options = 0x0;
	while (*args)
	{
		if (ft_strcmp(*args, "-a") == 0)
			lst->options += (0x1 << 1);
		if (ft_strcmp(*args, "-l") == 0)
			lst->options += (0x1 << 2);
		if (ft_strcmp(*args, "-R") == 0)
			lst->options += (0x1 << 3);
		if (ft_strcmp(*args, "-r") == 0)
			lst->options += (0x1 << 4);
		if (ft_strcmp(*args, "-t") == 0)
			lst->options += (0x1 << 5);
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