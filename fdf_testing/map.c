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

void	rotate_point_z(t_point	*point)
{
	float temp;

	temp = point->x;
	point->x = (point->x * cos(45 * (M_PI / 180))) + (point->y * sin(45 * (M_PI / 180)));
	point->y = (temp * -sin(45 * (M_PI / 180))) + (point->y * cos(45 * (M_PI / 180)));
}

void	rotate_point_x(t_point	*point)
{
	float temp;

	temp = point->y;
	point->y = (point->y * cos(atan(-sqrt(2)))) + (point->z * sin(atan(-sqrt(2))));
	point->z = (temp * -sin(atan(-sqrt(2)))) + (point->z * cos(atan(-sqrt(2))));
}

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
	y = 0;
	cur_pnt = 0;
	env->pnts = (t_point **)ft_memalloc(sizeof(t_point *) * env->height);
	if (env->pnts)
	{
		tmp = env->pnts_read;
		while (y < env->height)
		{
			x = 0;
			env->pnts[y] = ft_memalloc(sizeof(t_point) * env->width);
			while (x < env->width)
			{
				env->pnts[y][x].x = x;
				env->pnts[y][x].y = y;
				env->pnts[y][x].z = atoi(env->pnts_read);
				rotate_point_z(&env->pnts[y][x]);
				rotate_point_x(&env->pnts[y][x]);
				env->pnts_read += ft_numsize(atoi(env->pnts_read)) + 1;
				x++;
			}
			y++;
		}
		free(tmp);
	}
	else
		fdf_get_error(1, "Malloc failed line 45");
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
			fdf_get_error(1, "Invalid line length in file.");
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
		free(tmp);
		get_map_width(env, line);
		height++;
	}
	(env->height == 0) ? env->height = height : 0;
	close(fd);
	return (0);
}
