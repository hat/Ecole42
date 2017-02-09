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

int		get_coordinates(t_env *env)
{
	long	num_points;
	long	height;
	long	width;
	long	cur_pnt;

	printf("Width: %ld Height: %ld\n", env->width, env->height);
	height = 0;
	cur_pnt = 0;
	num_points = env->width * env->height;
	env->pnts = (t_point *)malloc(sizeof(t_point) * num_points);
	while (height < env->height)
	{
		width = 0;
		while (width < env->width)
		{
			env->pnts[cur_pnt].x = height;
			env->pnts[cur_pnt].y = width++;
			env->pnts[cur_pnt].z = 0;
			cur_pnt++;
		}
		height++;
	}
	// for (int i = 0; i < env->width * env->height; i++)
	// {
	// 	printf("Coordinates:\n");
	// 	printf("\tx: %ld y: %ld z: %ld\n", env->pnts[i].x, env->pnts[i].y, env->pnts[i].z);
	// }
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

int		get_map_size(t_env *env, int argc, char *argv[])
{
	int		fd;
	long	height;
	char	*line;

	height = 0;
	line = NULL;
	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			fdf_get_error(1, "Failed opening file.");
			return (1);
		}
		while (get_next_line(fd, &line))
		{
			get_map_width(env, line);
			height++;
		}
		if (env->height == 0)
			env->height = height;
		close(fd);
	}
	else
		fdf_get_error(1, "No argument.");
	return (0);
}
