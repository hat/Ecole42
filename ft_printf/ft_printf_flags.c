/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 11:50:11 by thendric          #+#    #+#             */
/*   Updated: 2017/01/02 11:54:52 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long	ft_vartype(t_input *input)
{
	int 	i;
	long	num;
	int 	islong;

	i = 0;
	islong = 0;
	while (input->flags[i])
	{
		if (input->flags[i] == 'l' || input->flags[i] == 'j')
			islong++;
		i++;
	}
	if (islong)
		num = (long)input->var;
	else
		num = (int)input->var;
	return (num);
}

int		ft_atoi_flags(const char *str)
{
	int		ans;
	int		i;
	int		neg;

	ans = 0;
	i = 0;
	neg = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32 || ft_isflag(str[i]))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			neg = -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		ans = (ans * 10) + (str[i] - '0');
		i++;
	}
	return (ans * neg);
}

char	*ft_callflags(t_input *input, char *str)
{
	if (input->flagminus)
		str = ft_flagwidth(input, str, 1);
	if (input->flagzero && !input->flagminus)
		str = ft_flagwidth(input, str, 0);
	if (input->flagpound)
		str = ft_flagpound(input, str);
	if (input->flagplus && ft_atoi(str) > 0)
		str = ft_flagplus(str);
	if (input->flagspace && ft_strlen(input->flags) == 1 && !input->flagminus)
		str = ft_flagspace(str);
	if (input->width && !input->flagminus)
		str = ft_flagwidth(input, str, 0);
	input->str = ft_strjoin(input->str, str);
	return (str);
}

void	ft_checkflags(t_input *input, char *str)
{
	int		i;
	int 	numcheck;

	i = 0;
	numcheck = 0;
	while (input->flags[i])
	{
		if (input->flags[i] >= '1' && input->flags[i] <= '9')
			numcheck++;
		if (input->flags[i] == '+')
			input->flagplus++;
		if (input->flags[i] == '#' && ft_strcmp(str, "0"))
			input->flagpound++;
		if (input->flags[i] == '-')
			input->flagminus++;
		if (input->flags[i] == ' ' && ft_strlen(input->flags) == 1 && str[0] != '-')
			input->flagspace++;
		if (input->flags[i] == '0' && !numcheck)
			input->flagzero++;
		i++;
	}
	str = ft_callflags(input, str);
	if (input->c == 'X')
		ft_touppercase(input->str);
}

int		ft_getflags(t_input *input)
{
	int		i;
	char	*c;

	i = 1;
	c = ft_strdup(input->form + 1);
	while (input->form[i] && !ft_isconversion(ft_tolower(input->form[i])))
		i++;
	c[i - 1] = '\0';
	input->flags = ft_strjoin(input->flags, c);
	input->width = ft_atoi_flags(input->flags);
	i = 0;
	while (input->flags[i] && input->flags[i] != '.')
		i++;
	input->precision = ft_atoi_flags(&input->flags[i + 1]);
	ft_memdel((void **)&c);
	return (ft_strlen(input->flags));
}
