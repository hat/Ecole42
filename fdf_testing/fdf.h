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

# define KEY_ESC 53
# define KEY_SPACE 49

// typedef struct s_line
// {
// 	long height;
// 	long width;
// }				t_line;

typedef struct s_point
{
	long	x;
	long	y;
	long	z;
}				t_crds;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	long	height;
	long	width;
	t_crds	*cords;
}				t_mlx;

# define COLOR 0xaaaa00

#endif
