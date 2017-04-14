/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:01:47 by mhalit            #+#    #+#             */
/*   Updated: 2017/02/19 17:50:46 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct		s_image
{
	int		bpp;
	int		size;
	int		endian;
	char	*data;
}					t_image;



void		mlx_pixel_image(t_image *env, int x, int y, int color)
{
	int pos;

	pos = (x * (env->bpp / 8) + (y * env->size));
	env->data[pos] = color;
	env->data[pos + 1] = color >> 8;
	env->data[pos + 2] = color >> 16;
	//env->data[pos + 3] = color >> 24;
}

int	main()
{
	t_image	*env;

	env = malloc(sizeof(t_image));
	void	*init = mlx_init();
	void	*win = mlx_new_window(init, 500, 500, "test");
	void	*image = mlx_new_image(init, 500, 500);
	int x = 0;
	int y = 0;
	
	env->data = mlx_get_data_addr(image, &env->bpp, &env->size, &env->endian);
	while (y < 499)
	{
		x = 0;
		while (x < 499)
		{
			mlx_pixel_image(env, x, y, 0x00FFFFF);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(init, win, image, 0, 0);
	mlx_string_put(init, win, 0, 0, 0, "Menu\n---------------\nSalut les amis\n-----------------");
	mlx_loop(init);
}