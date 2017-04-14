/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <thendric@student.42.us.org       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 13:22:21 by thendric          #+#    #+#             */
/*   Updated: 2017/04/10 13:22:23 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

# include <stdlib.h>
# include <libft.h>
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h> //GET MODIFIED TIME
# include <math.h> // Add to libft
# include <errno.h>

typedef struct	s_args
{
	char		a;
	char		l;
	char		R;
	char		r;
	char		t;
	int			count;
	char		*dir;
	t_list		*dirs;
	t_list		*dirs_pre;
}				t_args;

typedef struct	s_file
{
	char			*filename;
	struct stat		stats;
}				t_file;

void	parse_args(int argc, char *argv[], t_args *args);




/*** MAY NOT NEED ***/
int		check_bit(const int num, int byte);

#endif