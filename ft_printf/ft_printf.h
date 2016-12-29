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
	char		c;
	long long	size;
}				t_input;

int		ft_printf(const char *format, ...);
int 	ft_init(t_input *input);

#endif