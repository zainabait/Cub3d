/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:23:21 by zait-bel          #+#    #+#             */
/*   Updated: 2024/10/14 17:25:46 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

uint32_t    get_texture_pixel(mlx_image_t *texture, int x, int y)
{
    uint8_t    r;
    uint8_t    g;
    uint8_t    b;
    uint8_t    a;
    int        index;

    if (!texture)
        return (0);
    if (x >= 0 && (uint32_t)x < texture->width
        && y >= 0 && (uint32_t)y < texture->height)
    {
        index = (y * texture->width + x) * 4;
        r = texture->pixels[index];
        g = texture->pixels[index + 1];
        b = texture->pixels[index + 2];
        a = texture->pixels[index + 3];
        return (r << 24 | g << 16 | b << 8 | a);
    }
    return (0xFFFFFFFF);
}
void	render_3d(void *param)
{
	t_cube *cube = (t_cube *)param;
	int x;	
	x = -1;
	double ray = cube->player->angle - (FOV_ANGLE / 2);
	t_inter ch;
	t_inter cv;

	while (++x < SCREEN_WIDTH)
	{
		cv = find_vertical_intersection(cube, ray);
		ch = find_horizontal_intersection(cube, ray);
		calculate_closest_ray(ch, cv, cube);
		cube->ray[x].x = cube->hit->x;
		cube->ray[x].y = cube->hit->y;
		cube->ray[x].angle = ray;
		render_wall(cube, x, ray);
		ray += FOV_ANGLE / SCREEN_WIDTH;
	}
	render_minimap(cube);
}

void	render_wall(t_cube *cube, double x, double ray)
{
	double	distance;
	double	base_distance;
	double	wall_height;
	int		from_y;	
	int		to_y;

	distance = cube->hit->dist * cos(cube->player->angle - ray);
	base_distance = (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2);
	wall_height = (TILE_SIZE / distance) * base_distance;
	from_y = (SCREEN_HEIGHT / 2) - (wall_height / 2);
	to_y = from_y + wall_height;
    // cube->data->wall_x = 1;
	// cube->data->wall_x -= floor(cube->data->wall_x);
	// cube->data->tex_width = cube->data->no_image_texture->width;
	// cube->data->tex_height = cube->data->no_image_texture->height;
	// cube->data->texture_x = (int)(cube->data->wall_x * cube->data->tex_width) % cube->data->tex_width;
	// cube->data->step = (double)cube->data->tex_height / wall_height;
	// cube->data->texture_pos = (from_y - (SCREEN_HEIGHT / 2 - wall_height / 2)) * cube->data->step;
    // current_texture = cube->data->no_image_texture;
    // int y = from_y;
	// while (y < to_y)
	// {
	// 	cube->data->texture_y = (int)cube->data->texture_pos % cube->data->tex_height;
	// 	cube->data->texture_pos += cube->data->step;
	// 	uint32_t color = get_texture_pixel(current_texture, \
	// 		cube->data->texture_x, cube->data->texture_y);
	// 	mlx_put_pixel(cube->image, x, y, color);
	// 	y++;
	// }

    

	if (!cube->hit->ver_hit)
		bresenham_line(x, from_y, x, to_y, cube, 0xFFC0CBFF);
	else
		bresenham_line(x, from_y, x, to_y, cube, 0xb163ffb1);
	bresenham_line(x, from_y, x, 0, cube, 0x51158c51 );//sky
	bresenham_line(x, SCREEN_HEIGHT, x, to_y - 1, cube, 0xffa54fff);//floor
}
void render_minimap(void* param)
{
	t_cube *cube = param;
    int j;
    int x, y;
	size_t i;
	j = 0;

    while (j < cube->data->height)
    {
		i = 0;
        while (i < cube->data->width)
        {
            y = 0;
            while (y < TILE_SIZE / 5 - 1)
            {
				x = 0;
                while (x < TILE_SIZE / 5 - 1)
                {
            		if (cube->data->map[j][i] == '1')
                    	mlx_put_pixel(cube->image,i * TILE_SIZE / 5 + x, j * TILE_SIZE / 5 + y, 0xff0000ff);
					else
                    	mlx_put_pixel(cube->image, i * TILE_SIZE / 5 + x, j * TILE_SIZE / 5 + y, 0x00ff00ff);
					x++;
                }
				y++;
            }
			i++;
        }
		j++;
    }
	x =-1;
	draw_player(cube);
	while(++x < SCREEN_WIDTH)
	{
		bresenham_line(cube->player->x/5, cube->player->y/5, cube->ray[x].x/5, cube->ray[x].y/5, cube, 0xFFFFFFFF);
	}
}
void bresenham_line(long from_x, long from_y, long to_x, long to_y, t_cube *cub, uint32_t color)
{
    long diff[2], step[2], error[2], pos[2];

    diff[0] = labs(to_x - from_x);
    diff[1] = labs(to_y - from_y);
    step[0] = get_sign(from_x, to_x);
    step[1] = get_sign(from_y, to_y);
    error[0] = diff[0] - diff[1];
    pos[0] = from_x;
    pos[1] = from_y;
    while (pos[0] != to_x || pos[1] != to_y)
    {
        put_pixel_safe(cub->image, pos[0], pos[1], color);
        error[1] = 2 * error[0];
        if (error[1] > -diff[1])
        {
            error[0] -= diff[1];
            pos[0] += step[0];
        }
        if (error[1] < diff[0])
        {
            error[0] += diff[0];
            pos[1] += step[1];
        }
    }
}
void	put_pixel_safe(mlx_image_t *img, long x, long y, long color)
{
	if ((x < 0 || x >= SCREEN_WIDTH) || (y < 0 || y >= SCREEN_HEIGHT))
	{
		return ;
	}
	mlx_put_pixel(img, x, y, color);
}