/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_unsign.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 13:13:10 by thendric          #+#    #+#             */
/*   Updated: 2017/01/19 12:30:06 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base_unsign(unsigned long value, int base)
{
	unsigned long	size;
	unsigned long	temp;
	char			*numstr;
	char			*basenum;

	numstr = NULL;
	basenum = ft_strdup("0123456789abcdef");
	size = 1;
	temp = value;
	while ((temp /= base) > 0)
		size++;
	if (!(numstr = ft_strnew(size)))
		return (0);
	numstr[size] = '\0';
	while (*numstr)
		numstr++;
	temp = value;
	while (size > 0)
	{
		numstr[--size] = basenum[temp % base];
		temp /= base;
	}
	return (numstr);
}
