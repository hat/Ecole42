
#include "ft_ls.h"

char	*ft_substr(char *str, int pos, int len)
{
	char	*new_str;
	int		i;

	new_str = ft_strnew(len);
	i = 0;
	if (new_str == NULL)
		exit(1);
	while (i < len && str[i])
	{
		new_str[i] = str[i + pos];
		i++;
	}
	return (new_str);
}

//WTF IS THIS DOING?!??!?!?!?!

t_file	*get_all(t_all *lst, int i)
{
	void			*dir;
	struct dirent	*rdir;
	t_file			*head;
	t_file			*file;

	head = (t_file *)ft_memalloc(sizeof(t_file));
	file = head;

	dir = opendir(lst->dirv[i]);

		char			*path;
		struct stat		fileStat;

		path = ft_strnew(ft_strlen(lst->dirv[i]) + 1);
		path = ft_strjoin(lst->dirv[i], "/");
		//path = ft_strjoin(path, file);

	if (dir != NULL)
	{
		while ((rdir = readdir(dir)) != NULL)
		{
			head->name = ft_strnew(ft_strlen(lst->dirv[i]) + ft_strlen(rdir->d_name) + 1);
			if ( !(check_bit(lst->flags, 1)) ) //change to bitwise
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
	else if (lstat(path, &fileStat) < 0)
	{
		head->name = lst->dirv[i];
		head->isFile = 1;
		head->next = (t_file *)ft_memalloc(sizeof(t_file));
		head = head->next;
	}
	return (file);
}

void	get_dir(t_all *lst, int argc, char *argv[])
{
	int				i;
	struct stat		fileStat;

	i = 0;
	lst->path = (char **)ft_memalloc(sizeof(char *) * argc);
	while (++i < argc)
	{
		lst->path[i] = ft_strdup(argv[i]);
		if (ft_strcmp(ft_substr(argv[i], 0, 2), "--") == 0)
		{
			if (ft_strlen(argv[i]) > 2)
			{
				ft_putstr("ls: illegal option -- -\nusage: ft_ls"
					" [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
				exit(1);
			}
			lst->dash = 1;
		}
		else if ((*argv[i] != '-' && !lst->dash && opendir(argv[i])) || !lstat(lst->path[i], &fileStat))
		{
			lst->dirv[lst->dirc - 1] = ft_strdup(argv[i]);
			lst->dirc++;
		}
		else if (!opendir(argv[i]) && lstat(lst->path[i], &fileStat) && lst->dash)
			ft_printf("ls: %s: No such file or directory\n", argv[i]);
		else if (*argv[i] != '-')
		{
			ft_printf("ls: %s: No such file or directory\n", argv[i]);
			lst->dirv = NULL;
			lst->dirc = 0;
		}
	}
	lst->dirc = (lst->dirc == 1) ? 1 : lst->dirc - 1;
}
