/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 11:45:00 by thendric          #+#    #+#             */
/*   Updated: 2017/01/02 11:55:34 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_pickconvers(t_input *input)
{
	input->var = va_arg(input->ap, void *);
	if (input->c == 'i' || input->c == 'd' || input->c == 'D')
		ft_convers_id(input);
	if (input->c == 's')
		ft_convers_s(input);
	if (input->c == 'c' || input->c == 'C')
		ft_convers_c(input);
	if (input->c == 'f')
		ft_convers_f(input);
	if (input->c == '%')
		ft_convers_percent(input);
	if (input->c == 'o' || input->c == 'O')
		ft_convers_o(input);
	if (input->c == 'x' || input->c == 'X')
		ft_convers_x(input);
	if (input->c == 'u' || input->c == 'U')
		ft_convers_u(input);
	if (input->c == 'p')
		ft_convers_p(input);
	return (0);
}

int		ft_findconvers(t_input *input)
{
	int		i;
	int		is_space;
	char	c;

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
		if (ft_isconversion(c))
		{
			input->c = c;
			ft_pickconvers(input);
			break ;
		}
		i++;
	}
	input->form = input->form + 1;
	ft_init(input);
	return (0);
}

void	ft_resetflags(t_input *input)
{
	input->width = 0;
	input->negative = 0;
	input->precision = -1;
	input->flagplus = 0;
	input->flagpound = 0;
	input->flagspace = 0;
	input->flagminus = 0;
	input->flagzero = 0;
	ft_bzero(input->flags, ft_strlen(input->flags));
	//ft_memdel((void **)&input->str);
	//ft_strdel(&(input->str));
}

int		ft_percentsign(t_input *input)
{
	char	*prev;

	prev = ft_strndup(input->form, (ft_strchr(input->form, '%') - input->form));
	input->form = input->form + (ft_strchr(input->form, '%') - input->form);
	ft_resetflags(input);
	input->negative = 0;
	if (!input->str)
		input->str = ft_strdup(prev);
	else
		input->str = ft_strjoin(input->str, prev);
	ft_memdel((void **)&prev);
	ft_findconvers(input);
	return (0);
}

int		ft_printf(const char *format, ...)
{
	t_input	*input;
	va_list	ap;
	size_t	ret;

	input = ft_init_tinput(format);
	va_start(input->ap, format);
	ft_init(input);
	va_end(ap);
	ft_putstr(input->str);
	ret = ft_strlen(input->str) + input->size;
	ft_memdel((void **)&input->str);
	free(input);
	return (ret);
}
