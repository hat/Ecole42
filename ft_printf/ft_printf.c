
// RETURN VALUES
// These functions return the number of characters printed (not including
// the trailing `\0' used to end output to strings). These functions return a negative value if an error occurs.

//TODO Check if no parameters were passed in
	// if no params and no % print *format
	// if no params and % print error (more % conversions than data arguments)

//TODO Check for % symbol in *format

#include "ft_printf.h"

int 	ft_convers_percent(void)
{
	ft_putchar('%');
	printf("Exit\n");
	return (0);
}

int 	ft_convers_c(va_list ap)
{
	char c;

	c = va_arg(ap, int);
	ft_putchar(c);
	return (0);
}

int 	ft_convers_s(va_list ap)
{
	char *str;

	str = va_arg(ap, char *);
	ft_putstr(str);
	return (0);
}

int 	ft_convers_f(va_list ap)
{
	int num;

	num  = va_arg(ap, int);
	ft_putnbr(num);
	return (0);
}

int 	ft_convers_i(va_list ap)
{
	int num;

	num  = va_arg(ap, int);
	ft_putnbr(num);
	return (0);
}

int 	ft_convers_d(va_list ap)
{
	int num;

	num  = va_arg(ap, int);
	ft_putnbr(num);
	return (0);
}

int 	ft_pickconvers(char c, va_list ap)
{
	if (c == 'd')
		ft_convers_d(ap);
	if (c == 'i')
		ft_convers_i(ap);
	if (c == 's')
		ft_convers_s(ap);
	if (c == 'c')
		ft_convers_c(ap);
	if (c == 'f')
		ft_convers_f(ap);
	if (c == '%')
		ft_convers_percent();
	return (0);
}

int 	ft_findconvers(const char *format, va_list ap)
{
	int i;
	int is_space;
	char c;

	i = 0;
	is_space = 0;
	if (format[0] == ' ')
	{
		is_space = 1;
		i++;
	}
	while (format[i] && format[i] != ' ')
	{
		c = format[i];
		if (c == 'd' || c == 'i' || c == 's' || c == 'c'
			|| c == '%' || c == 'f')
		{
			ft_pickconvers(c, ap);
		}
		i++;
	}
	//One must be number of chars after %
	ft_init(format + 1, ap);
	return (0);
}

int 	ft_percentsign(const char *format, va_list ap)
{
	char 	*prev;

	prev = ft_strndup(format, (ft_strchr(format, '%') - format));
	ft_putstr(prev);
	free(prev);
	ft_findconvers(ft_strchr(format, '%') + 1, ap);
	return (0);
}

int 	ft_init(const char *format, va_list ap)
{
	if (!(ft_strchr(format, '%')))
		ft_putstr(format);
	else if (ft_strchr(format, '%'))
		ft_percentsign(format, ap);
	return (0);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;

	va_start(ap, format);
	ft_init(format, ap);
	va_end(ap);
	return (0);
}