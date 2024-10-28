/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:32:14 by mohimi            #+#    #+#             */
/*   Updated: 2024/10/27 21:09:56 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

void	put_pixel_mini(mlx_image_t *img, long x, long y, long color)
{
	if ((x < 0 || x >= 200) || (y < 0 || y >= 200))
	{
		return ;
	}
	put_pixel_safe(img, x, y, color);
}

void	render_minimap_background(t_cube *cube)
{
	int		j;
	size_t	i;

	j = 0;
	while (j < cube->data->height * TILE_SIZE)
	{
		i = 0;
		while (i < cube->data->width * TILE_SIZE)
		{
			put_pixel_mini(cube->image, i, j, 0x1f1f1f);
			i++;
		}
		j++;
	}
}

void	render_player_view(t_cube *cube)
{
	double		a;
	t_line_y	line_y;
	t_line_y	line_x;

	a = -0.05;
	while (a < 0.05)
	{
		line_y.from = 100;
		line_y.to = 100 + 200 * sin(cube->player->angle + a);
		line_x.from = 100;
		line_x.to = 100 + 200 * cos(cube->player->angle + a);
		bresenham_line_mini(line_x, line_y, cube);
		a += 0.005;
	}
}

void	render_minimap_tile(t_cube *cube, int i, int j)
{
	int	x;
	int	y;

	y = 0;
	while (y <= TILE_SIZE / 4)
	{
		x = 0;
		while (x <= TILE_SIZE / 4)
		{
			if (cube->data->map[j][i] == '1')
				put_pixel_mini(cube->image,
					i * TILE_SIZE / 4 + x - cube->player->x / 4 + 100,
					j * TILE_SIZE / 4 + y - cube->player->y / 4 + 100,
					0x71597F71);
			else if (cube->data->map[j][i] == 'D')
				put_pixel_mini(cube->image,
					i * TILE_SIZE / 4 + x - cube->player->x / 4 + 100,
					j * TILE_SIZE / 4 + y - cube->player->y / 4 + 100,
					0xFF7F50FF);
			else
				put_pixel_mini(cube->image,
					i * TILE_SIZE / 4 + x - cube->player->x / 4 + 100,
					j * TILE_SIZE / 4 + y - cube->player->y / 4 + 100,
					0xF0D9FFF0);
			x++;
		}
		y++;
	}
}

void	render_minimap(t_cube *cube)
{
	int		j;
	size_t	i;

	j = 0;
	render_minimap_background(cube);
	while (j < cube->data->height)
	{
		i = 0;
		while (i < cube->data->width)
		{
			render_minimap_tile(cube, i, j);
			i++;
		}
		j++;
	}
	draw_player(cube);
	render_player_view(cube);
}
