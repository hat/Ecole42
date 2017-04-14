#ifndef FT_LS
# define FT_LS

# include <stdlib.h>
# include <libft.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <time.h> //GET MODIFIED TIME
#include <math.h> // Add to libft

typedef struct	s_file
{
	char			*name;
	int				isFile;
	struct s_file	*next;
}				t_file;

typedef struct	s_all
{
	int				flags;
	int				dash;
	//char			*dir;
	int				dirc;
	char			**path;
	char			**dirv;
}				t_all;

int		check_bit(const int num, int byte);
void	bubblesort(t_file *head);
void	bubblesort_dirs(t_all *lst);

/* parse_flags.c */
void	get_options(t_all *lst, int argc, char *argv[]);

/* printer.c */
void	print_dirs_long(t_all *lst, t_file *file, int i);
void	print_dirs_reverse(t_all *lst, t_file *file, int i, int nl);
void	print_dirs(t_all *lst, t_file *file, int i);
void	check_print_dirs(t_all *lst, t_file *file, int i);

/* getter.c */
void	get_dir(t_all *lst, int argc, char *argv[]);
t_file	*get_all(t_all *lst, int i);

#endif
