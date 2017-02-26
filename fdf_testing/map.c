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

size_t	ft_wordcount(char const *s, char c)
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

void	rot_z_axis(t_point *point, float angle)
{
	float	temp;

	temp = point->x;
	point->x = (point->x * cos(angle) + (point->y * sin(angle)));
	point->y = (temp * -sin(angle) + (point->y * cos(angle)));
}

void	rot_x_axis(t_point *point, float angle)
{
	float	temp;

	temp = point->y;
	point->y = (point->y * cos(angle) + (point->z * sin(angle)));
	point->z = (temp * -sin(angle) + (point->z * cos(angle)));
}

long	ft_numsize(long num)
{
	long	size;

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
	env->pnts[env->cords.y][env->cords.x].x = env->cords.x;
	env->pnts[env->cords.y][env->cords.x].y = env->cords.y;
	env->pnts[env->cords.y][env->cords.x].z =
								atoi(env->pnts_read[env->cords.i]);
	env->pnts[env->cords.y][env->cords.x].x *= env->trans.scale;
	env->pnts[env->cords.y][env->cords.x].y *= env->trans.scale;
	env->pnts[env->cords.y][env->cords.x].z *= env->trans.scale;
	env->pnts[env->cords.y][env->cords.x].x += env->trans.transx;
	env->pnts[env->cords.y][env->cords.x].y += env->trans.transy;
	rot_z_axis(&env->pnts[env->cords.y][env->cords.x], 45 * (M_PI / 180));
	rot_x_axis(&env->pnts[env->cords.y][env->cords.x], atan(-sqrt(2)));
	env->pnts[env->cords.y][env->cords.x].x += (WIN_WIDTH / 2);
	env->pnts[env->cords.y][env->cords.x].y += (WIN_HEIGHT / 2);
	env->cords.x++;
	env->cords.i++;
}

int		get_coordinates(t_env *env)
{
	env->trans.scale = (env->wdth > env->hght) ? (WIN_HEIGHT / 2)
					/ (env->hght - 1) : (WIN_WIDTH / 2) / (env->wdth - 1);
	env->trans.transx = (WIN_WIDTH - (env->wdth - 1) * env->trans.scale) / 2;
	env->trans.transy = (WIN_HEIGHT - (env->hght - 1) * env->trans.scale) / 2;
	env->cords.y = 0;
	env->cords.cur_pnt = 0;
	env->cords.i = 0;
	env->pnts = (t_point **)ft_memalloc(sizeof(t_point *) * env->hght);
	if (env->pnts)
	{
		while (env->cords.y < env->hght)
		{
			env->cords.x = 0;
			env->pnts[env->cords.y] =
				(t_point *)ft_memalloc(sizeof(t_point) * env->wdth);
			while (env->cords.x < env->wdth)
			{
				set_map(env);
			}
			env->cords.y++;
		}
	}
	else
		return (fdf_get_error(1, "Malloc failed line 45"));
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
	if (fd < 0)
		return (fdf_get_error(1, "ERROR: fine not found."));
	while (get_next_line(fd, &line))
	{
		width = ft_wordcount(line, ' ');
		height++;
		line = ft_strjoin(line, " ");
		full = ft_strjoin(full, line);
		free(line);
		(env->wdth == 0) ? env->wdth = width : 0;
	}
	(env->hght == 0) ? env->hght = height : 0;
	env->pnts_read = ft_strsplit(full, ' ');
	close(fd);
	return (0);
}
