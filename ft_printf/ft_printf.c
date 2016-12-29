
// RETURN VALUES
// These functions return the number of characters printed (not including
// the trailing `\0' used to end output to strings)-> These functions return a negative value if an error occurs->

//TODO Check if no parameters were passed in
	// if no params and no % print *format
	// if no params and % print error (more % conversions than data arguments)

//TODO Check for % symbol in *format

//TODO Use a struct to store everything as to not print if error occurs later

#include "ft_printf.h"

int 	ft_convers_percent(t_input *input)
{
	input->str = ft_strjoin(input->str, "%");
	input->form = input->form + 1;
	return (0);
}

int 	ft_convers_c(t_input *input)
{
	char 	*c;

	c = ft_strnew(2);
	c[0] = va_arg(input->ap, int);
	c[1] = '\0';
	input->str = ft_strjoin(input->str, c);
	input->form = input->form + 1;
	return (0);
}

int 	ft_convers_s(t_input *input)
{
	char *str;

	str = va_arg(input->ap, char *);
	input->str = ft_strjoin(input->str, str);
	//1 will be number of flags!
	input->form = input->form + 1;
	return (0);
}

int 	ft_convers_id(t_input *input)
{
	int num;
	char 	*numstr;

	num  = va_arg(input->ap, int);
	numstr = ft_itoa(num);
	input->str = ft_strjoin(input->str, numstr);
	//1 will be number of flags!
	input->form = input->form + 1;
	return (0);
}

int 	ft_convers_f(t_input *input)
{
	double 	num;
	char 	*numstr;

	numstr = NULL;
	num  = va_arg(input->ap, double);
	//Create print number with decimal point
	//ft_putnbr(num);
	return (0);
}

int 	ft_pickconvers(t_input *input)
{
	if (input->c == 'i' || input->c == 'd')
		ft_convers_id(input);
	if (input->c == 's')
		ft_convers_s(input);
	if (input->c == 'c')
		ft_convers_c(input);
	if (input->c == 'f')
		ft_convers_f(input);
	if (input->c == '%')
		ft_convers_percent(input);
	return (0);
}

int 	ft_findconvers(t_input *input)
{
	int i;
	int is_space;
	char c;

	i = 0;
	is_space = 0;
	if (input->form[0] == ' ')
	{
		is_space = 1;
		i++;
	}
	while (input->form[i] && input->form[i] != ' ')
	{
		c = input->form[i + 1];
		if (c == 'd' || c == 'i' || c == 's' || c == 'c'
			|| c == '%' || c == 'f')
		{
			input->c = c;
			input->form = input->form + i;
			ft_pickconvers(input);
		}
		i++;
	}
	input->form = input->form + 1;
	ft_init(input);
	return (0);
}

int 	ft_percentsign(t_input *input)
{
	char 	*prev;

	prev = ft_strndup(input->form, (ft_strchr(input->form, '%') - input->form));
	input->form = input->form + (ft_strchr(input->form, '%') - input->form);
	//printf("IF: %s\n", input->form);
	if (!input->str)
		input->str = ft_strdup(prev);
	else
		input->str = ft_strjoin(input->str, prev);
	free(prev);
	ft_findconvers(input);
	return (0);
}

int 	ft_init(t_input *input)
{
	if (!(ft_strchr(input->form, '%')))
	{
		if (!input->str)
			input->str = ft_strdup(input->form);
		else
			input->str = ft_strjoin(input->str, input->form);
	}
	else if (ft_strchr(input->form, '%'))
		ft_percentsign(input);
	return (0);
}

t_input	*ft_init_tinput(void)
{
	t_input 	*new;

	new = (t_input *)malloc(sizeof(t_input));
	new->form = NULL;
	new->str = NULL;
	new->size = 0;

	return (new);
}

int		ft_printf(const char *format, ...)
{
	t_input		*input;
	va_list		ap;

	input = ft_init_tinput();
	va_start(input->ap, format);
	input->form = (char *)format;
	ft_init(input);
	va_end(ap);
	ft_putstr(input->str);
	return (0);
}