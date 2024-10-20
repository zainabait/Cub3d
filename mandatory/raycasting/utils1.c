/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:05:27 by mohimi            #+#    #+#             */
/*   Updated: 2024/10/20 11:14:53 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	apply_shadow(uint32_t *color, t_cube *cube, double max_distance)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	double		intensity;

	intensity = 1 - (cube->ray->dis / max_distance);
	if (intensity < 0.3)
		intensity = 0.3;
	r = (*color >> 24) & 0xFF;
	g = (*color >> 16) & 0xFF;
	b = (*color >> 8) & 0xFF;
	r *= intensity;
	g *= intensity;
	b *= intensity;
	*color = (r << 24) | (g << 16) | (b << 8) | 0xff;
}

void	cal_wall_dimen(t_cube *cube, int *from_y, int *to_y, double *w_height)
{
	double	base_distance;

	base_distance = (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2);
	*w_height = (TILE_SIZE / cube->ray->dis) * base_distance;
	*from_y = (SCREEN_HEIGHT / 2) - (*w_height / 2);
	*to_y = *from_y + *w_height;
	if (*from_y < 0)
		*from_y = 0;
	if (*to_y > SCREEN_HEIGHT)
		*to_y = SCREEN_HEIGHT;
}

void	ft_texture_to_image(t_cube *cube)
{
	cube->data->no_image_texture = mlx_texture_to_image \
		(cube->mlx, cube->data->no_texture);
	if (!cube->data->no_image_texture)
		ft_error_message("Error: 'No' texture encountered");
	cube->data->so_image_texture = mlx_texture_to_image \
		(cube->mlx, cube->data->so_texture);
	if (!cube->data->so_image_texture)
		ft_error_message("Error: 'So' texture encountered");
	cube->data->we_image_texture = mlx_texture_to_image \
		(cube->mlx, cube->data->we_texture);
	if (!cube->data->we_image_texture)
		ft_error_message("Error: 'We' texture encountered");
	cube->data->ea_image_texture = mlx_texture_to_image \
		(cube->mlx, cube->data->ea_texture);
	if (!cube->data->ea_image_texture)
		ft_error_message("Error: 'Ea' texture encountered");
}

void    ft_clear_image(mlx_image_t *img)
{
    uint32_t        i;
    uint32_t        j;
    unsigned int    clear;

    i = 0;
    clear = 255 << 24 | 255 << 16 | 255 << 8 | 0;
    while (i < img->height)
    {
        j = 0;
        while (j < img->width)
        {
            mlx_put_pixel(img, j, i, clear);
            j++;
        }
        i++;
    }
}

void	ft_mouse(double xpos, double ypos, void *param)
{
	t_cube	*cub;

	(void)ypos;
	cub = (t_cube *)param;
	mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_HIDDEN);
	if (cub->cursor_hidden && cub->player->prev_x > xpos)
		cub->player->angle -= fabs(cub->player->prev_x - xpos) * 0.004;
	else if (cub->cursor_hidden && cub->player->prev_x < xpos)
		cub->player->angle += fabs(cub->player->prev_x - xpos) * 0.004;
	cub->player->prev_x = xpos;
}

int	mlx_data_init(t_cube *cube)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	cube->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", true);
	if (!cube->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	cube->image = mlx_new_image(cube->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!cube->image)
	{
		mlx_close_window(cube->mlx);
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	if (mlx_image_to_window(cube->mlx, cube->image, 0, 0) == -1)
	{
		mlx_close_window(cube->mlx);
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	return (0);
}

int	data_init(t_cube *cube, t_player *player, t_inter *hit, t_ray *ray)
{
	cube->hit = hit;
	cube->ray = ray;
	cube->player = player;
	cube->player->angle = -1 * M_PI / 2;
	if (mlx_data_init(cube))
		return (1);
	return (0);
}
