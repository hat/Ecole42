/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 11:02:16 by thendric          #+#    #+#             */
/*   Updated: 2017/02/03 11:02:17 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

#define WIN_HEIGHT 600
#define WIN_WIDTH 500

# define KEY_ESC 53
# define KEY_SPACE 49

typedef struct s_point
{
	long	x;
	long	y;
	long	z;
}				t_point;

typedef struct s_env
{
	void	*mlx;
	void	*window;
	char	**pnts_read;
	long	height;
	long	width;
	t_point	**pnts;

	long	x;
	long	y;
	long	i;
	long	cur_pnt;
	long	max_map_size;

	long	scale;
	long	transx;
	long	transy;

	int		dx;
	int		sx;
	int		dy;
	int		sy;
	int		err;
	int		e2;
}				t_env;

# define COLOR 0xF2CFE0

/*
** Draw functions
*/
void	draw_circle(t_env *env, int x0, int y0, int x);
void	draw_line(t_env *env, int x0, int y0, int x1, int y1);
void	draw_box(t_env *env, int x0, int y0, int x1, int y1);
void	draw_grid(t_env *env);
void	draw_fill(t_env *env);

/*
** Map functions
*/
int		get_coordinates(t_env *env);
int		get_map_width(t_env *env, long counter);
int		get_map_size(t_env *env, char *argv[]);

/*
** Helper functions
*/
int		fdf_get_error(int error, char *string);

#endif
