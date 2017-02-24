/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 20:08:48 by thendric          #+#    #+#             */
/*   Updated: 2017/01/31 20:16:38 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

long	ft_numsize(long num)
{
	long size;

	size = 0;
	if (num < 0)
	{
		num *= -1;
		size++;
	}
	if (num == 0)
		size++;
	while (num)
	{
		num /= 10;
		size++;
	}
	return (size);
}

int		get_coordinates(t_env *env)
{
	long	x;
	long	y;
	long	cur_pnt;
	long	max_map_size;
	char	*tmp;

	max_map_size = 0;
	max_map_size = env->width > env->height ? env->width : env->height;
	printf("Width: %ld Height: %ld\n", env->width, env->height);
	x = -1;
	cur_pnt = 0;
	env->pnts = (t_point **)ft_memalloc(sizeof(t_point *) * env->height);
	if (env->pnts)
	{
		tmp = env->pnts_read;
		while (x < env->height)
		{
			y = 0;
			env->pnts[x] = ft_memalloc(sizeof(t_point) * env->width);
			while (y < env->width)
			{
				env->pnts[x][y].x = x;
				env->pnts[x][y].y = y;
				env->pnts[x][y].z = atoi(env->pnts_read);
				env->pnts_read += ft_numsize(atoi(env->pnts_read)) + 1;
				y++;
			}
			x++;
		}
		free(tmp);
	}
	else
	{
		printf("Failed mallocing for map points");
	}
	return (0);
}

int		get_map_width(t_env *env, char *line)
{
	long	width;
	char	**data;

	width = 0;
	data = ft_strsplit(line, ' ');
	while (*data)
	{
		width++;
		data++;
	}
	if (env->width == 0)
		env->width = width;
	else
	{
		if (width != env->width)
		{
			printf("Env->width: %ld Width: %ld\n", env->width, width);
			fdf_get_error(1, "Invalid line length in file.");
		}
	}
	return (0);
}

int		get_map_size(t_env *env, char *argv[])
{
	int		fd;
	long	height;
	char	*line;
	char	*tmp;

	height = 0;
	line = NULL;
	env->pnts_read = ft_strnew(0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		fdf_get_error(1, "Failed opening file.");
		return (1);
	}
	while (get_next_line(fd, &line))
	{
		tmp = env->pnts_read;
		env->pnts_read = ft_strjoin(env->pnts_read, line);
		printf("Bout to free\n");
		free(tmp);
		printf("Freed it!\n");
		get_map_width(env, line);
		height++;
	}
	(env->height == 0) ? env->height = height : 0;
	close(fd);
	return (0);
}
