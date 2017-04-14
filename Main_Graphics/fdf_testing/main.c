/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 20:08:48 by thendric          #+#    #+#             */
/*   Updated: 2017/01/31 20:16:38 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		fdf_get_error(int error, char *string)
{
	ft_printf("%s\n", string);
	return (error);
}

long	ft_wordcount(char const *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			words++;
		while (*s != c && *s)
			s++;
	}
	return (words);
}

void	parse_map(t_env *env, int fd)
{
	char	*line;
	char	*full;

	full = ft_strnew(1);
	while ((get_next_line(fd, &line)) > 0)
	{
		if (!env->wdth)
			env->wdth = ft_wordcount(line, ' ');
		else if (env->wdth != ft_wordcount(line, ' '))
		{
			fdf_get_error(1, "ERROR: map has invalid width\n");
			break ;
		}
		env->hght++;
		line = ft_strjoin(line, " ");
		full = ft_strjoin(full, line);
		free(line);
	}
	env->pnts_read = ft_strsplit(full, ' ');
	close(fd);
	get_coordinates(env);
}

void	run_graphics(t_env *env)
{
	draw(env);
	mlx_key_hook(env->win, key_manager, env);
	mlx_mouse_hook(env->win, mouse_manager, env);
	mlx_expose_hook(env->win, get_expose, env);
	mlx_loop(env->mlx);
}

int		main(int argc, char *argv[])
{
	t_env	*env;
	int		fd;

	if (argc > 1)
	{
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			ft_printf("error: Unable to open file");
		env = (t_env *)ft_memalloc(sizeof(t_env));
		env->mlx = mlx_init();
		env->win = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "FDF");
		env->clr1 = 0xFF0000;
		env->clr2 = 0xFFFFFF;
		setup_colors(env);
		parse_map(env, fd);
		get_coordinates(env);
		isometric(env);
		run_graphics(env);
		ft_memdel((void *)&env->crds);
		ft_memdel((void *)&env->pnts);
		ft_memdel((void *)&env->clrs);
		ft_memdel((void *)&env);
	}
	else
		return (fdf_get_error(1, "USAGE: ./fdf {filename}"));
	return (0);
}
