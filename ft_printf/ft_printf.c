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
	if (input->c == 'u' || input->c == 'U' || input->c == 'D')
		ft_convers_uUD(input);
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

int		ft_percentsign(t_input *input)
{
	char	*prev;

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

int		ft_init(t_input *input)
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
	t_input	*new;

	new = (t_input *)malloc(sizeof(t_input));
	new->form = ft_strdup((char *)format);
	new->flags = ft_strnew(1);
	new->str = NULL;
	new->size = 0;
	return (new);
}

int		ft_printf(const char *format, ...)
{
	t_input	*input;
	va_list	ap;

	input = ft_init_tinput(format);
	va_start(input->ap, format);
	ft_init(input);
	va_end(ap);
	ft_putstr(input->str);
	return (ft_strlen(input->str));
}
