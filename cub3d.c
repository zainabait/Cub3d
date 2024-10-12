/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:08:10 by zait-bel          #+#    #+#             */
/*   Updated: 2024/10/12 17:01:34 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char map[10][14] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '1', '0', '1', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '0', '0', '0', '1', '1', '0', '0', '0', '1'},
	{'1', '1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1'},
	{'1', '1', 'N', '0', '1', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '1', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};

int move_speed = 5;

bool	is_wall(int x, int y, t_cube *cub)
{
	(void)cub;
	if (x < 0 || x > 14 * TILE_SIZE || y < 0 || y > 10 * TILE_SIZE)
		return (1);
	if (map[y / TILE_SIZE][x / TILE_SIZE] == '1')
		return (1);
	return (0);
}

void	put_pixel_safe(mlx_image_t *img, long x, long y, long color)
{
	if ((x < 0 || x >= SCREEN_WIDTH) || (y < 0 || y >= SCREEN_HEIGHT))
	{
		return ;
	}
	mlx_put_pixel(img, x, y, color);
}

int get_sign(int a, int b)
{
	if (a < b)
		return (1);
	return (-1);
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

t_inter	find_vertical_intersection(t_cube *cube, double angle)
{
	t_inter first_touch;
	t_inter next_step;
	t_inter check;

	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	first_touch.x = floor(cube->player->x / TILE_SIZE) * TILE_SIZE;
	if (angle > M_PI * 1.5 || angle < M_PI / 2)
		first_touch.x += TILE_SIZE;
	first_touch.y = cube->player->y + (first_touch.x - cube->player->x) * tan(angle);
	next_step.x = TILE_SIZE;
	if (angle < M_PI * 1.5 && angle > M_PI / 2)
		next_step.x *= -1;
	next_step.y = TILE_SIZE * tan(angle);
	if (next_step.y > 0 && !(angle > 0 && angle < M_PI))
		next_step.y *= -1;
	if (next_step.y < 0 && angle > 0 && angle < M_PI)
		next_step.y *= -1;
	check.x = first_touch.x;
	check.y = first_touch.y;
	while (!(check.x < 0 || check.x > 14 * TILE_SIZE || check.y < 0 || check.y > 10 * TILE_SIZE))
	{
		if (angle > M_PI * 0.5 && angle < M_PI * 1.5)
			check.x--;
		if (is_wall(check.x, check.y, cube))
			break;
		check.x += next_step.x;
		check.y += next_step.y;
	}
	return (check);
}

t_inter	find_horizontal_intersection(t_cube *cube, double angle)
{
	t_inter first_touch;
	t_inter next_step;
	t_inter check;

	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	first_touch.y = floor(cube->player->y / TILE_SIZE) * TILE_SIZE;
	if (angle > 0 && angle < M_PI)
		first_touch.y += TILE_SIZE;
	first_touch.x = cube->player->x + (first_touch.y - cube->player->y) / tan(angle);
	if (first_touch.x > 14 * TILE_SIZE)
		first_touch.x = 14 * TILE_SIZE - 1;
	next_step.y = TILE_SIZE;
	if (!(angle > 0 && angle < M_PI))
		next_step.y *= -1;
	next_step.x = TILE_SIZE / tan(angle);
	if (next_step.x > 0 && angle < M_PI * 1.5 && angle > M_PI / 2)
		next_step.x *= -1;
	if (next_step.x < 0 && !(angle < M_PI * 1.5 && angle > M_PI / 2))
		next_step.x *= -1;
	check = first_touch;
	while (!(check.x < 0 || check.x > 14 * TILE_SIZE || check.y < 0 || check.y > 10 * TILE_SIZE))
	{
		if (angle > M_PI && angle < M_PI * 2)
			check.y--;
		if (is_wall(check.x, check.y, cube))
			break;
		check.x += next_step.x;
		check.y += next_step.y;
	}
	return (check);
}

void	initialize_position(char map[10][14], double *x, double*y)
{
	int	j;
	int	i;

	j = 0;
	while (j < 10)
	{
		i = 0;
		while (i < 14)
		{
			if (map[j][i] == 'N')
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

void	calculate_closest_ray(t_inter ch, t_inter cv, t_cube *cube)
{
	double h_dis;
	double v_dis;

	h_dis = sqrt(pow(cube->player->x - ch.x, 2) + pow(cube->player->y - ch.y, 2));
	v_dis = sqrt(pow(cube->player->x - cv.x, 2) + pow(cube->player->y - cv.y, 2));
	
	if (h_dis < v_dis)
	{
		cube->hit->dist = h_dis;
		cube->hit->x = ch.x;
		cube->hit->y = ch.y;
		cube->hit->ver_hit = 0;
		return ;
	}
	cube->hit->dist = v_dis;
	cube->hit->x = cv.x;
	cube->hit->y = cv.y;
	cube->hit->ver_hit = 1;
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
	if (cube->hit->ver_hit)
		bresenham_line(x, from_y, x, to_y, cube, 0xFFFFFFFF);
	else
		bresenham_line(x, from_y, x, to_y, cube, 0xDDDDDDFF);
	bresenham_line(x, from_y, x, 0, cube, 0x0000FFFF);
	bresenham_line(x, SCREEN_HEIGHT, x, to_y - 1, cube, 0x00FF00FF);
}


void draw_player(void* param)
{
	t_cube *cube = param;
	int x, y;
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

void render_minimap(void* param)
{
	t_cube *cube = param;
    int i, j;
    int x, y;
	j = 0;

    while (j < 10)
    {
		i = 0;
        while (i < 14)
        {
            y = 0;
            while (y < TILE_SIZE / 5 - 1)
            {
				x = 0;
                while (x < TILE_SIZE / 5 - 1)
                {
            		if (map[j][i] == '1')
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
	
	draw_player(cube);
}

void	render_3d(void *param)
{
	t_cube *cube = (t_cube *)param;
	int x;	
	x = -1;
	double ray = cube->player->angle - (FOV_ANGLE / 2);
	t_inter ch;
	t_inter cv;
	mlx_delete_image(cube->mlx, cube->image);
	cube->image = mlx_new_image(cube->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(cube->mlx, cube->image, 0, 0);
	while (++x < SCREEN_WIDTH)
	{
		cv = find_vertical_intersection(cube, ray);
		ch = find_horizontal_intersection(cube, ray);
		calculate_closest_ray(ch, cv, cube);
		render_wall(cube, x, ray);
		// bresenham_line(cube->player->x / 5, cube->player->y / 5, cube->hit->x / 5, cube->hit->y / 5, cube, 502061);
		ray += FOV_ANGLE / SCREEN_WIDTH;
	}
	render_minimap(cube);
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
	posx[0] = cos(cube->player->angle) * move_speed;
	posx[1] = cos(cube->player->angle + M_PI / 2) * move_speed;
	posy[0] = sin(cube->player->angle) * move_speed;
	posy[1] = sin(cube->player->angle + M_PI / 2) * move_speed;
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

int main()
{
	t_cube		*cube;
	t_player	*player;
	t_inter		hit;

	cube = malloc(sizeof(t_cube));
	player = malloc(sizeof(t_player));
	cube->hit = &hit;
	cube->player = player;
	cube->player->angle = 0;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	if (!(cube->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(1);
	}
	if (!(cube->image = mlx_new_image(cube->mlx, SCREEN_WIDTH, SCREEN_HEIGHT)))
	{
		mlx_close_window(cube->mlx);
		puts(mlx_strerror(mlx_errno));
		return(1);
	}
	if (mlx_image_to_window(cube->mlx, cube->image, 0, 0) == -1)
	{
		mlx_close_window(cube->mlx);
		puts(mlx_strerror(mlx_errno));
		return(1);
	}
	initialize_position(map, &player->x, &player->y);
	mlx_loop_hook(cube->mlx, render_3d, cube);
	mlx_key_hook(cube->mlx, handle_key_input, cube);
	mlx_image_to_window(cube->mlx, cube->image, 0, 0);
	mlx_loop(cube->mlx);
}
