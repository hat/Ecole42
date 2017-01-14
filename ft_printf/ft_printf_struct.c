/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 15:03:52 by thendric          #+#    #+#             */
/*   Updated: 2017/01/13 15:04:27 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	ft_memdel((void **)&input->flags);
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
	new->negative = 0;
	new->flagplus = 0;
	new->flagpound = 0;
	new->flagspace = 0;
	new->flagminus = 0;
	new->flagzero = 0;
	new->precision = -1;
	return (new);
}
