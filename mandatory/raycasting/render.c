/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:23:21 by zait-bel          #+#    #+#             */
/*   Updated: 2024/10/18 12:58:53 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_init_der(double *ray, t_cube *cube)
{
	cube->ray->is_down = *ray > 0 && *ray < M_PI;
	cube->ray->is_up = !cube->ray->is_down;
	cube->ray->is_right = *ray < M_PI / 2 || *ray > (3 * M_PI) / 2;
	cube->ray->is_left = !cube->ray->is_right;
}

void	render_3d(void *param)
{
	t_inter	ch;
	t_inter	cv;
	t_cube	*cube;
	double	ray;
	int		x;

	x = -1;
	cube = (t_cube *)param;
	ray = cube->player->angle - (FOV_ANGLE / 2);
	while (++x < SCREEN_WIDTH)
	{
		ray = normalize_angle(ray);
		ft_init_der(&ray, cube);
		cv = find_vertical_intersection(cube, ray);
		ch = find_horizontal_intersection(cube, ray);
		calculate_closest_ray(ch, cv, cube);
		1 && (cube->ray[x].x = cube->hit->x, cube->ray[x].y = cube->hit->y);
		cube->ray[x].angle = ray;
		render_wall(cube, x, ray);
		ray += FOV_ANGLE / SCREEN_WIDTH;
	}
	render_minimap(cube);
}

void	render_wall(t_cube *cube, double x, double ray)
{
	double		wall_height;
	int			from_y;
	int			to_y;
	mlx_image_t	*cur_tex;

	cube->ray->dis = cube->hit->dist * cos(cube->player->angle - ray);
	cal_wall_dimen(cube, &from_y, &to_y, &wall_height);
	cur_tex = find_texture(cube);
	if (!cur_tex)
		ft_error_message("Error: No texture");
	sel_calculate_texture(cube, cur_tex);
	calculate_tex_pos(cube, cur_tex, wall_height, from_y);
	cube->ray->i = from_y;
	while (cube->ray->i < to_y)
	{
		cube->data->text_y = (int)cube->data->text_pos % cube->data->tex_height;
		cube->ray->color = get_texture_pixel(cur_tex, \
		cube->data->text_x, cube->data->text_y);
		apply_shadow(&cube->ray->color, cube, 700);
		mlx_put_pixel(cube->image, x, cube->ray->i, cube->ray->color);
		cube->data->text_pos += cube->data->step;
		cube->ray->i++;
	}
	bresenham_line(x, from_y, x, 0, cube, cube->data->c_color);
	bresenham_line(x, SCREEN_HEIGHT, x, to_y - 1, cube, cube->data->f_c);
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
                    	put_pixel_safe(cube->image,i * TILE_SIZE / 5 + x, j * TILE_SIZE / 5 + y, 0xff0000ff);
					else
                    	put_pixel_safe(cube->image, i * TILE_SIZE / 5 + x, j * TILE_SIZE / 5 + y, 0x00ff00ff);
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

void	bresenham_line(long from_x, long from_y, long to_x, long to_y, t_cube *cub, uint32_t color)
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
