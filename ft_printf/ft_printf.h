#ifndef FT_PRINTF_H
# define FT_PRINTF_H

//TEST
#include <stdio.h>

# include <stdarg.h>
# include "../includes/libft/libft.h"

int		ft_printf(const char *format, ...);
int 	ft_init(const char *format, va_list ap);

#endif