/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <thendric@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 13:17:44 by thendric          #+#    #+#             */
/*   Updated: 2017/04/10 13:17:53 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void set_flags(char *argv, t_args *args)
{
	int i;

	i = 0;
	while (argv[i++])
	{
		args->a = (argv[i] == 'a') ? 1 : args->a;
		args->l = (argv[i] == 'l') ? 1 : args->l;
		args->R = (argv[i] == 'R') ? 1 : args->R;
		args->r = (argv[i] == 'r') ? 1 : args->r;
		args->t = (argv[i] == 't') ? 1 : args->t;
	}
}

void	parse_args(int argc, char *argv[], t_args *args)
{
	int		c;
	int		end;

	c = 0;
	end = 0;
	while (++c < argc)
	{
		if (*argv[c] == '-')
		{
			if (argv[c][1] == '-')
				break ;
			else if (*argv[c] == '-' && !end)
				set_flags(argv[c], args);
			else
				ft_printf("ls: %s: No such file or directory\n", argv[c]);
		}
		else
			end = 1;
	}
}