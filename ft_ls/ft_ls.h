#ifndef FT_LS
# define FT_LS

# include <stdlib.h>
# include <libft.h>

typedef struct	s_file
{
	char			*name;
	struct s_file	*next;
}				t_file;

typedef struct	s_all
{
	int				options;
	//char			*dir;
	int				dirc;
	char			**dirv;
}				t_all;

void	bubblesort(t_file *head);
void	bubblesort_dirs(t_all *lst);

#endif