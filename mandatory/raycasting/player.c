/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:20:57 by zait-bel          #+#    #+#             */
/*   Updated: 2024/10/14 18:08:18 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	initialize_position(t_data *data, double *x, double *y)
{
	int		j;
	size_t	i;

	j = 0;
	while (j < data->height)
	{
		i = 0;
		while (i < data->width)
		{
			if (data->map[j][i] == 'N' || data->map[j][i] == 'S'
			|| data->map[j][i] == 'W' || data->map[j][i] == 'E')
			{
				*x = i * TILE_SIZE + TILE_SIZE / 2;
				*y = j * TILE_SIZE + TILE_SIZE / 2;
				return ;
			}
			i++;
		}
		j++;
	}
}

void	draw_player(void *param)
{
	t_cube	*cube;
	int		x;
	int		y;

	cube = param;
	y = -2;
	while (y <= 2)
	{
		x = -2;
		while (x <= 2)
		{
			mlx_put_pixel(cube->image, cube->player->x / 5 + x, cube->player->y / 5 + y, 0xFFFA);
			x++;
		}
		y++;
	}
}
void handle_key_input(mlx_key_data_t keydata, void* param)
{
	t_cube *cube = param;
    if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(cube->mlx);
	else if (keydata.key == MLX_KEY_W)
		cube->player->wd = 1;
	else if (keydata.key == MLX_KEY_S)
		cube->player->wd = -1;
	else if (keydata.key == MLX_KEY_A)
		cube->player->ard = -1;
	else if (keydata.key == MLX_KEY_D)
		cube->player->ard = 1;
	else if (keydata.key == MLX_KEY_RIGHT)
		cube->player->td = 1;
	else if (keydata.key == MLX_KEY_LEFT)
		cube->player->td = -1;
	if (keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S)
			cube->player->wd = 0;
		if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
			cube->player->ard = 0;
		if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
			cube->player->td = 0;
	}
}
