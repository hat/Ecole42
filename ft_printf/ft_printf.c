
// RETURN VALUES
// These functions return the number of characters printed (not including
// the trailing `\0' used to end output to strings)-> These functions return a negative value if an error occurs->

//TODO Check if no parameters were passed in
	// if no params and no % print *format
	// if no params and % print error (more % conversions than data arguments)

//TODO Check for % symbol in *format

//TODO Use a struct to store everything as to not print if error occurs later

#include "ft_printf.h"

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
	if (input->c == 'o' || input->c == 'O')
		ft_convers_oO(input);
	if (input->c == 'x' || input->c == 'X')
		ft_convers_xX(input);
	if (input->c == 'u' || input->c == 'U')
		ft_convers_uU(input);
	if (input->c == 'p')
		ft_convers_p(input);
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
	while (input->form[i])
	{
		c = input->form[i + 1];
		if (c == 'd' || c == 'i' || c == 's' || c == 'c'
			|| c == '%' || c == 'f' || c == 'o' || c == 'x'
			|| c == 'u' || c == 'O' || c == 'X' || c == 'p'
			|| c == 'U')
		{
			input->c = c;
			ft_pickconvers(input);
			break;
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

t_input	*ft_init_tinput(const char *format)
{
	t_input 	*new;

	new = (t_input *)malloc(sizeof(t_input));
	new->form = ft_strdup((char *)format);//(char *)format;
	new->flags = ft_strnew(1);
	new->str = NULL;
	new->size = 0;

	return (new);
}

int		ft_printf(const char *format, ...)
{
	t_input		*input;
	va_list		ap;

	input = ft_init_tinput(format);
	va_start(input->ap, format);
	ft_init(input);
	va_end(ap);
	ft_putstr(input->str);
	return (0);
}