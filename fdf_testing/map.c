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

void	isometric(t_env *env)
{
	printf("Transx: %ld\n", env->trans.transx);
	env->trans.scale = ceil((env->wdth > env->hght) ? ((float)WIN_HEIGHT / 2) / ((float)env->hght - 1) : ((float)WIN_WIDTH / 2) / ((float)env->wdth - 1));
	env->trans.transx = (WIN_WIDTH - (env->wdth - 1) * env->trans.scale) / 2;
	env->trans.transy = (WIN_HEIGHT - (env->hght - 1) * env->trans.scale) / 2;
	env->cords->x = 0;
	printf("Just scale: %f\n", env->trans.scale);
	printf(" Win_Height: %d Env->hght %ld Win_Width %d Env-wdth: %ld Scale: %f Transx: %ld Transy: %ld\n", WIN_HEIGHT, env->hght, WIN_WIDTH, env->wdth, env->trans.scale, env->trans.transx, env->trans.transy);
	printf("Scale %f Math: %ld\n", env->trans.scale, (long)WIN_WIDTH - ((long)env->wdth - 1) * (long)env->trans.scale);
	printf("%f ::: %f \n", 45 * (M_PI / 180), atan(-sqrt(2)));
	while (env->cords->x < env->hght)
	{
		env->cords->y = 0;
		while (env->cords->y < env->wdth)
		{
			env->pnts[env->cords->x][env->cords->y].x *= env->trans.scale;
			env->pnts[env->cords->x][env->cords->y].y *= env->trans.scale;
			env->pnts[env->cords->x][env->cords->y].z *= env->trans.scale;
			env->pnts[env->cords->x][env->cords->y].x -= env->trans.transx;
			env->pnts[env->cords->x][env->cords->y].y -= env->trans.transy;
			rot_z_axis(&env->pnts[env->cords->x][env->cords->y], 45 * (M_PI / 180));
			rot_x_axis(&env->pnts[env->cords->x][env->cords->y], atan(-sqrt(2)));
			env->pnts[env->cords->x][env->cords->y].x += (WIN_HEIGHT / 2);
			env->pnts[env->cords->x][env->cords->y].y += (WIN_WIDTH / 2);
			env->cords->y++;
		}
		env->cords->x++;
	}
}

int		get_coordinates(t_env *env)
{
	if (!(env->cords = (t_coords *)ft_memalloc(sizeof(t_coords))))
		return (fdf_get_error(1, "ERROR: malloc failed"));
	if (!(env->pnts = (t_point **)ft_memalloc(sizeof(t_point *) * env->hght)))
		return (fdf_get_error(1, "ERROR: malloc failed"));
	while (env->cords->y < env->hght)
	{
		env->cords->x = 0;
		if (!(env->pnts[env->cords->y] = (t_point *)ft_memalloc(sizeof(t_point) * env->wdth)))
			return (fdf_get_error(1, "ERROR: malloc failed"));
		while (env->cords->x < env->wdth)
		{
			env->pnts[env->cords->y][env->cords->x].x = env->cords->x;
			env->pnts[env->cords->y][env->cords->x].y = env->cords->y;
			env->pnts[env->cords->y][env->cords->x].z = atoi(env->pnts_read[env->cords->i]);
			env->cords->x++;
			env->cords->i++;
		}
		env->cords->y++;
	}
	return (0);
}

void		parse_map(t_env *env, int fd)
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
