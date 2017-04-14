/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <thendric@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 13:01:55 by thendric          #+#    #+#             */
/*   Updated: 2017/04/10 13:17:35 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/******

	TESTING
	
******/

void	ft_check_flags(t_args *args)
{
	if (args->a)
		ft_putstr("DEBUG: -a\n");
	if (args->l)
		ft_putstr("DEBUG: -l\n");
	if (args->R)
		ft_putstr("DEBUG: -R\n");
	if (args->r)
		ft_putstr("DEBUG: -r\n");
	if (args->t)
		ft_putstr("DEBUG: -t\n");
}

void	read_dir(DIR *d, t_args *args, t_list *lst, t_file *file)
{
	struct dirent	*dir;

	while ((dir = readdir(d)) > 0)
	{
		if (args->a && dir->d_name[0] == '.')
			continue ;
		gen_info(file, args->dir, dir->d_name);
		ft_lst_add_back(lst, ft_lstnew(file, sizeof(file)));
	}
	ft_lstsort(lst, args->r, args->t ? time_cmp : name_cmp);
	closedir(d);
}


int		handle_error(t_args *args, t_file *file, t_list *lst)
{
	if (errno == 13)
	{
		ft_printf("ls: %s: %s\n", args->dir, strerror(errno));
		return (1);
	}
	args->dir[ft_strlen(args->dir) - 1] = 0;
	errno = 0;
	get_info(file, "", args->dir);
	if (errno)
	{
		ft_printf("ls: %s: %s\n", args->dir, strerror(errno));
		return (1);
	}
	ft_lst_add_back(file, ft_lstnew(file, sizeof(t_path)));
	return (0);
}

void	ft_ls(t_args *args)
{
	DIR		*dir;
	t_list	*lst;
	t_file	*file;
	char	*cur_dir;

	lst = NULL;
	args->dir = ft_strjoin(args->dir ? args->dir : ".", "/");
	cur_dir = ft_strdup(args->dir);
	errno = 0;
	dir = opendir(args->dir);
	if (errno)
	{
		if (handle_error(args, file, lst))
			return ;
	}
	else
	{
		read_dir(dir, args, lst, file);
			if (args->l && lst)
				ft_printf("total %lld\n", addblocks(lst));
	}
	iterate_files(lst, args, cur_dir);
}


/*************

	TESTING FINISHED

************/

int		main(int argc, char *argv[])
{
	t_args		*args;
	t_file		*file;

	args = (t_args *)ft_memalloc(sizeof(args));
	file = (t_file *)ft_memalloc(sizeof(t_file));
	parse_args(argc, argv, args);
	args->dir = ".";
	if (argc == 1)
	{
		//ft_ls(args);
		ft_putchar('#');
	}
	else
	{
		//sort
		//while dirs
			//get info
			//if file
				//addtoback
			//go to next
		//iterate through dirs
		ft_putchar('!');
	}
	/** BELOW TO CHECK  **/

	ft_check_flags(args);

	/**    END CHECK    **/
	return (0);
}