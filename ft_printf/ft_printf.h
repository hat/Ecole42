#ifndef FT_PRINTF_H
# define FT_PRINTF_H

//TEST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# include <stdarg.h>
# include "../includes/libft/libft.h"

typedef struct 	s_read
{
	va_list		ap;
	char		*form;
	char		*str;
	char		*flags;
	char		c;
	long long	size;
	int 		width;
}				t_input;

/*
** Declare digit functions
*/
int 	ft_convers_id(t_input *input);
int 	ft_convers_uUD(t_input *input);
int 	ft_convers_f(t_input *input);
int 	ft_convers_oO(t_input *input);
int 	ft_convers_xX(t_input *input);
/*
** Declare char functions
*/
int 	ft_convers_percent(t_input *input);
int 	ft_convers_c(t_input *input);
int 	ft_convers_s(t_input *input);
int 	ft_convers_p(t_input *input);
/*
** Declare universal helper functions
*/
int		ft_isflag(char c);
int 	ft_isconversion(char c);
char	ft_getconversion(char *str);
/*
** Declare functionality functions
*/
void	ft_add_width(t_input *input, size_t var_size, char *str);
void	ft_checkflags(t_input *input, char *str);
int		ft_getflags(t_input *input);
int 	ft_init(t_input *input);
int		ft_printf(const char *format, ...);

#endif