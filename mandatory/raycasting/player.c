/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:20:57 by zait-bel          #+#    #+#             */
/*   Updated: 2024/10/13 15:56:25 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	initialize_position(t_data *data, double *x, double *y)
{
	int	j;
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
	int i, j;
	i = cube->player->x / TILE_SIZE;
	j = cube->player->y / TILE_SIZE;
	int posx[2];
	int posy[2];

	// mlx_delete_image(cube->mlx, cube->image);
	posx[0] = cos(cube->player->angle) * SPEED;
	posx[1] = cos(cube->player->angle + M_PI / 2) * SPEED;
	posy[0] = sin(cube->player->angle) * SPEED;
	posy[1] = sin(cube->player->angle + M_PI / 2) * SPEED;
    if (keydata.action != MLX_RELEASE)
    {
        if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(cube->mlx);
		else if (keydata.key == MLX_KEY_W && !is_wall(cube->player->x + posx[0], cube->player->y + posy[0], cube))
		{
			cube->player->x += posx[0];
			cube->player->y += posy[0];
		}
		else if (keydata.key == MLX_KEY_S && !is_wall(cube->player->x - posx[0], cube->player->y - posy[0], cube))
		{
            cube->player->x -= posx[0];
            cube->player->y -= posy[0];
		}
		else if (keydata.key == MLX_KEY_A && !is_wall(cube->player->x - posx[1], cube->player->y - posy[1], cube))
		{
            cube->player->x -= posx[1];
            cube->player->y -= posy[1];
		}
		else if (keydata.key == MLX_KEY_D && !is_wall(cube->player->x + posx[1], cube->player->y + posy[1], cube))
		{
            cube->player->x += posx[1];
            cube->player->y += posy[1];
		}
		else if (keydata.key == MLX_KEY_RIGHT)
			cube->player->angle += 0.3;
		else if (keydata.key == MLX_KEY_LEFT)
			cube->player->angle -= 0.3;
    }
	cube->image = mlx_new_image(cube->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	render_3d(cube);
}