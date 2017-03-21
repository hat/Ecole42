#ifndef FT_LS
# define FT_LS

typedef struct	s_file
{
	char			*name;
	struct s_file	*next;
}				t_file;

typedef struct	s_all
{
	int				options;
	t_file			*file;
}				t_all;

#endif