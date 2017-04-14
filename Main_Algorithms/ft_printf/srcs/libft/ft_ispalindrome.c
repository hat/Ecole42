/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ispalindrome.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <thendric@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:29:14 by thendric          #+#    #+#             */
/*   Updated: 2016/11/06 23:31:59 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ispalindrome(char *str)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!str)
		return (0);
	while (str[j])
		j++;
	while (i < j)
	{
		if (str[++i] != str[--j])
			return (0);
	}
	return (1);
}
