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

static size_t	ft_wordcount(char const *s, char c)
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

void	rotate_point_z(t_point	*point)
{
	float temp;

	temp = point->x;
	point->x = (point->x * cos(45 * (M_PI / 180)) + (point->y * sin(45 * (M_PI / 180))));
	point->y = (temp * -sin(45 * (M_PI / 180)) + (point->y * cos(45 * (M_PI / 180))));
}

void	rotate_point_x(t_point	*point)
{
	float temp;

	temp = point->y;
	point->y = (point->y * cos(atan(-sqrt(2))) + (point->z * sin(atan(-sqrt(2)))));
	point->z = (temp * -sin(atan(-sqrt(2))) + (point->z * cos(atan(-sqrt(2)))));
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

void	set_map(t_env *env)
{
	env->pnts[env->y][env->x].x = env->x;
	env->pnts[env->y][env->x].y = env->y;
	env->pnts[env->y][env->x].z = atoi(env->pnts_read[env->i]);
	env->pnts[env->y][env->x].x *= env->scale;
	env->pnts[env->y][env->x].y *= env->scale;
	env->pnts[env->y][env->x].z *= env->scale;
	env->pnts[env->y][env->x].x -= env->transx;
	env->pnts[env->y][env->x].y -= env->transy;
	rotate_point_z(&env->pnts[env->y][env->x]);
	rotate_point_x(&env->pnts[env->y][env->x]);
	env->pnts[env->y][env->x].x += (WIN_WIDTH / 2);
	env->pnts[env->y][env->x].y += (WIN_HEIGHT / 2);
	env->x++;
	env->i++;	
}

int		get_coordinates(t_env *env)
{
	env->scale = (env->width > env->height) ? (WIN_HEIGHT / 2) / (env->height - 1) : (WIN_WIDTH / 2) / (env->width - 1);
	env->transx = (WIN_WIDTH - ((env->width - 1) * env->scale)) / 2;
	env->transy = (WIN_HEIGHT - ((env->height - 1) * env->scale)) / 2;
	env->y = 0;
	env->cur_pnt = 0;
	env->i = 0;
	env->pnts = (t_point **)ft_memalloc(sizeof(t_point *) * env->height);
	if (env->pnts)
	{
		while (env->y < env->height)
		{
			env->x = 0;
			env->pnts[env->y] = (t_point *)ft_memalloc(sizeof(t_point) * env->width);
			while (env->x < env->width)
			{
				set_map(env);
			}
			env->y++;
		}
	}
	else
		fdf_get_error(1, "Malloc failed line 45");
	return (0);
}

int		get_map_size(t_env *env, char *argv[])
{
	int		fd;
	long	height;
	long	width;
	char	*line;
	char	*full;

	height = 0;
	full = ft_strnew(1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		fdf_get_error(1, "FILE!\n");
	if (fd < 0)
	{
		fdf_get_error(1, "Failed opening file.");
		return (1);
	}
	while (get_next_line(fd, &line))
	{
		width = ft_wordcount(line, ' ');
		height++;
		line = ft_strjoin(line, " ");
		full = ft_strjoin(full, line);
		free(line);
		(env->width == 0) ? env->width = width : 0;
	}
	(env->height == 0) ? env->height = height : 0;
	env->pnts_read = ft_strsplit(full, ' ');
	close(fd);
	return (0);
}
