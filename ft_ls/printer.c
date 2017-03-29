#include "ft_ls.h"

void	print_dirs_long(t_all *lst, t_file *file, int i)
{
	char			*path;
	struct stat		fileStat;
	struct passwd	*pw;
	struct group	*gr;
	char			*date;


	if (!file->isFile)
	{
		path = ft_strnew(ft_strlen(lst->dirv[i]) + 1);
		path = ft_strjoin(lst->dirv[i], "/");
		path = ft_strjoin(path, file->name);
	}
	else
	{
		path = ft_strdup(file->name);
	}


    if(lstat(path, &fileStat) < 0)
    {
    	ft_printf("ERROR: Could not get stats of: %s\n", path);
        return ;
    }
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
    ft_printf(" %s\n", file->name);
    ft_strdel(&date);
}

void	print_dirs_reverse(t_all *lst, t_file *file, int i, int nl)
{
	if (!file)
		return ;
	if (lst->dirc > 1 && nl != -1)
	{
		ft_printf("%s:\n", lst->dirv[i]);
		nl = -1;
	}
	print_dirs_reverse(lst, file->next, i, nl);
	if (file->name)
	{
		if (check_bit(lst->options, 2))
			print_dirs_long(lst, file, i);
		else
			ft_printf("%s\n", file->name);
	}
}

void	print_dirs(t_all *lst, t_file *file, int i)
{
	if (lst->dirc > 1 && (ft_strchr(lst->dirv[i], '/') || *lst->dirv[i] == '.'))
		ft_printf("%s:\n", lst->dirv[i]);
	while (file->next)
	{
		if ( check_bit(lst->options, 2) )
			print_dirs_long(lst, file, i);
		else
			ft_printf("%s\n", file->name);
		file = file->next;
	}
}

void	check_print_dirs(t_all *lst, t_file *file, int i)
{
	if ( check_bit(lst->options, 4) )
		print_dirs_reverse(lst, file, i, 1);
	// else if ( check_bit(lst->options, 3) )
	// 	print_dirs_recursively(lst);
	else
		print_dirs(lst, file, i);
}