#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <time.h> //GET MODIFIED TIME
#include "ft_ls.h"

#include <libft.h>

#include <math.h> // Add to libft

int		check_bit(const int num, int byte)
{
	return ((num) & (1<<(byte)));
}

//ERROR HERE WHEN CHANGING DIR TO PRINT
//POSSIBLY BECAUSE NOT INCLUDING ../ ???

void	print_dirs_long(t_all *lst, char *file)
{
	char			*path;
	struct stat		fileStat;
	struct passwd	*pw;
	struct group	*gr;
	char			*date;

	path = ft_strnew(ft_strlen(lst->dirv[0]) + 1);

	path = ft_strjoin(lst->dirv[0], "/");

	path = ft_strjoin(path, file);

	//ERROR EXISTS HERE!!!
    if(lstat(path, &fileStat) < 0)
        return ;

    date = ft_strnew(10);

    //FILE PERMISSIONS

    ft_printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-"); // can possibly be 'l'
    ft_printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    ft_printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    ft_printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    ft_printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    ft_printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    ft_printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    ft_printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    ft_printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    ft_printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");

    //NUMBER OF LINKS

    ft_printf(" %d", fileStat.st_nlink);

    //USER ID

    pw = getpwuid(fileStat.st_uid);

    ft_printf(" %s", pw->pw_name);

    //USER GROUP

    gr = getgrgid(fileStat.st_gid);

    ft_printf("  %s", gr->gr_name);

    //FILE SIZE

    ft_printf(" %6d",fileStat.st_size);

    //FILE DATE/TIME

    strftime(date, 20, " %b %d %R", localtime(&(fileStat.st_ctime)));
    ft_printf("%s", date);

    //FILE NAME

    ft_printf(" %s\n", file);

    ft_strdel(&date);
}

void	print_dirs_reverse(t_all *lst, t_file *file, int i)
{
	ft_putstr("Seg\n");
	if (!file)
		return ;
	print_dirs_reverse(lst, file->next, i);
	//if (lst->dirc > 1)
		//ft_printf("%s:\n", lst->dirv[i]);
	if (file->name)
	{
		if (check_bit(lst->options, 2))
			print_dirs_long(lst, file->name);
		else
			ft_printf("%s\n", file->name);
		//file = file->next;
	}
}

void	print_dirs(t_all *lst, t_file *file, int i)
{
	if (lst->dirc > 1)
		ft_printf("%s:\n", lst->dirv[i]);
	while (file->next)
	{
		if ( check_bit(lst->options, 2) )
			print_dirs_long(lst, file->name);
		else
			ft_printf("%s\n", file->name);
		file = file->next;
	}
}

void	check_print_dirs(t_all *lst, t_file *file, int i)
{
	if ( check_bit(lst->options, 4) )
		print_dirs_reverse(lst, file, i);
	// else if ( check_bit(lst->options, 3) )
	// 	print_dirs_recursively(lst);
	else
		print_dirs(lst, file, i);
}

t_file	*get_all(t_all *lst, int i)
{
	void			*dir;
	struct dirent	*rdir;
	t_file			*head;
	t_file			*file;

	head = (t_file *)ft_memalloc(sizeof(t_file));
	file = head;

	dir = opendir(lst->dirv[i]);
	if (dir != NULL)
	{
		while ((rdir = readdir(dir)) != NULL)
		{
			head->name = ft_strnew(ft_strlen(lst->dirv[i]) + ft_strlen(rdir->d_name) + 1);
			if ( !(check_bit(lst->options, 1)) ) //change to bitwise
			{
				if (*rdir->d_name != '.')
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
	else
	{
		file = NULL;
		ft_printf("ls: %s: No such file or directory\n", lst->dirv[0]);
	}
	return (file);
}

void	get_dir(t_all *lst, int argc, char *argv[])
{
	int		i;
	char	dbl_dash;

	i = 1;
	dbl_dash = 0;
	while (i < argc)
	{
		if (*argv[i] == '-' && *argv[i + 1] == '-')
			dbl_dash = 0;
		if (*argv[i] != '-' || dbl_dash)
			lst->dirv[i - 1] = ft_strdup(argv[i]);
		i++;
	}
	lst->dirc = ((i - 1) == 0) ? 1 : (i - 1);
}

void	get_options(t_all *lst, int argc, char *argv[])
{
	int i = 1;
	int j = 0;

	lst->options = 0x0;
	while (i < argc)
	{
		if (*argv[i])
		{
			j = 1;
			if (argv[i][j + 1] == '-')
				break ;
			while (j < (int)ft_strlen(argv[i]))
			{
				if (argv[i][j] == 'a')
					lst->options += (0x1 << 1);
				else if (argv[i][j] == 'l')
					lst->options += (0x1 << 2);
				else if (argv[i][j] == 'R')
					lst->options += (0x1 << 3);
				else if (argv[i][j] == 'r')
					lst->options += (0x1 << 4);
				else if (argv[i][j] == 't')
					lst->options += (0x1 << 5);
				else if (argv[i][j] == 't')
					lst->options += (0x1 << 5);
				j++;
			}
		}
		i++;
	}
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
		ft_putstr("Gto opts\n");
	get_dir(lst, argc, argv);
	if (argc > 1)
		get_options(lst, argc, argv);
	while (cur_dir < lst->dirc)
	{
		file = get_all(lst, cur_dir);
		if (file)
		{
			bubblesort(file);
			check_print_dirs(lst, file, cur_dir);
		}
		if (lst->dirc > 1 && cur_dir + 1 != lst->dirc)
			ft_printf("\n");
		cur_dir++;
	}
}