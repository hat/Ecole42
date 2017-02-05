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

#include "fdf.h"

void	draw_circle(void *mlx, void *window, int x0, int y0, int x)
{
	int y = 0;
	int err = 0;

	while (x >= y)
	{
		mlx_pixel_put(mlx, window, x0 + x, y0 + y, COLOR);
		mlx_pixel_put(mlx, window, x0 + x, y0 + y, COLOR);
		mlx_pixel_put(mlx, window, x0 + y, y0 + x, COLOR);
		mlx_pixel_put(mlx, window, x0 - y, y0 + x, COLOR);
		mlx_pixel_put(mlx, window, x0 - x, y0 + y, COLOR);
		mlx_pixel_put(mlx, window, x0 - x, y0 - y, COLOR);
		mlx_pixel_put(mlx, window,x0 - y, y0 - x, COLOR);
		mlx_pixel_put(mlx, window,x0 + y, y0 - x, COLOR);
		mlx_pixel_put(mlx, window,x0 + x, y0 - y, COLOR);

		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

void	draw_line(void *mlx, void *window, int x0, int y0, int x1, int y1)
{
	int dx;
	int sx;
	int dy;
	int sy;
	int err;
	int e2;

	dx = abs(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = abs(y1 - y0);
	sy = y0 < y1 ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;

	while (1)
	{
		mlx_pixel_put(mlx, window, x0, y0, COLOR);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void draw_box(void *mlx, void *window, int x0, int y0, int x1, int y1)
{
	draw_line(mlx, window, x0, y0, x0, y1);
	draw_line(mlx, window, x0, y0, x1, y0);
	draw_line(mlx, window, x0, y1, x1, y1);
	draw_line(mlx, window, x1, y0, x1, y1);
}

void	draw_grid(void *mlx, void *window)
{
	int x;
	int y;

	x = 0;
	while (x < 1200)
	{
		y = 1200;
		while (y > 0)
		{
			draw_line(mlx, window, x, y, x + 5, y + 5);
			y += 5;
		}
		x += 5;
	}
}

void	draw(void *mlx, void *window)
{
	draw_circle(mlx, window, 600, 600, 150);
	draw_line(mlx, window, 600, 600, 600, 1000);
	draw_box(mlx, window, 300, 300, 600, 600);
	draw_grid(mlx, window);
}

int		fdf_get_error(int error, char *string)
{
	ft_printf("%s\n", string);
	return (error);
}

int		get_coordinates(t_mlx *mlx, char *line)
{
	char	**data;

	printf("Line: %s\n", line);
	data = ft_strsplit(line, ' ');
	while (*data)
	{
		printf("%s\n", *data);
		printf("%d\n", ft_atoi(*data));
		mlx->width++;
		data++;
	}
	printf("Width: %ld\n", mlx->width);
	return (0);
}

int		get_map(t_mlx *mlx, int argc, char *argv[])
{
	int		fd;
	char	*line;

	line = NULL;
	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			fdf_get_error(1, "Failed opening file.");
			return (1);
		}
		while (get_next_line(fd, &line) == 1)
		{
			get_coordinates(mlx, line);
			mlx->height++;
		}
		close(fd);
	}
	else
		fdf_get_error(1, "No argument.");
	return (0);
}

int		key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		exit (1); //Exits program executable
	}
	if (keycode == KEY_SPACE)
	{
		printf("Space!\n");
	}
	return (0);
}

int		main(int argc, char *argv[])
{
	t_mlx	*mlx;

	mlx = (t_mlx *)ft_memalloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx, 1200, 1200, "Playground");
	get_map(mlx, argc, argv);
	//draw(mlx->mlx, mlx->window);
	mlx_key_hook(mlx->window, key_hook, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
