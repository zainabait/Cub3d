/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:08:10 by zait-bel          #+#    #+#             */
/*   Updated: 2024/10/09 17:32:06 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <math.h>

char map[10][14] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '0', '0', '1', '1', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '1', '1', '0', '1', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '1', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
	{'1', 'N', '1', '0', '1', '1', '0', '1', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '1', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '1', '1', '0', '1', '0', '1', '0', '0', '0', '1'},
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

void	my_mlx_put_pixel(mlx_image_t *img, double x, double y, double color)
{
	if ((x < 0 || x >= 14 * TILE_SIZE) || (y < 0 || y >= 10 * TILE_SIZE))
	{
		return ;
	}
	mlx_put_pixel(img, x, y, color);
}


void DDA(double X0, double Y0, double X1, double Y1, t_cube *cub, uint32_t color) 
{
    // calculate dx & dy 
    double dx = X1 - X0; 
    double dy = Y1 - Y0; 
  
    // calculate steps required for generating pixels 
    double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy); 
  
    // calculate increment in x & y for each steps 
    double Xinc = dx / steps; 
    double Yinc = dy / steps; 
  
    // Put pixel for each step 
    double X = X0; 
    double Y = Y0; 
    for (int i = 0; i <= steps; i++) {
		if ((X < 0 || X >= 14 * TILE_SIZE) || (Y < 0 || Y >= 10 * TILE_SIZE))
		{
			return ;
		}
      	my_mlx_put_pixel(cub->image, X, Y, color); // put pixel at (X,Y) 
        X += Xinc; // increment in x at each step 
        Y += Yinc; // increment in y at each step 
        // delay(100); // for visualization of line- 
                    // generation step by step 
    } 
}
// void bresenham_line(int x0, int y0, int x1, int y1, t_cube *cube)
// {
//     int dx = abs(x1 - x0);
//     int dy = abs(y1 - y0);

//     int sx = (x0 < x1) ? 1 : -1;  // Step direction in x
//     int sy = (y0 < y1) ? 1 : -1;  // Step direction in y

//     int err = dx - dy;  // Initial error

//     while (x0 != x1 || y0 != y1)
//     {
//         my_mlx_put_pixel(cube->image, x0, y0, 0xFFFA);  // Plot the current pixel

//         int e2 = 2 * err;  // Calculate double the error

//         // Adjust the error and move in the x-direction if the error is greater than -dy
//         if (e2 > -dy)
//         {
//             err -= dy;
//             x0 += sx;  // Step in the x-direction
//         }

//         // Adjust the error and move in the y-direction if the error is less than dx
//         if (e2 < dx)
//         {
//             err += dx;
//             y0 += sy;  // Step in the y-direction
//         }
//     }
// }

int get_sign(int a, int b)
{
	if (a < b)
		return (1);
	return (-1);
}

void bresenham_line(double from_x, double from_y, double to_x, double to_y, t_cube *cub, uint32_t color)
{
    double diff[2], step[2], error[2], pos[2];

    diff[0] = fabs(to_x - from_x);
    diff[1] = fabs(to_y - from_y);
    step[0] = get_sign(from_x, to_x);
    step[1] = get_sign(from_y, to_y);
    error[0] = diff[0] - diff[1];
    pos[0] = from_x;
    pos[1] = from_y;
    while (pos[0] != to_x || pos[1] != to_y)
    {
        my_mlx_put_pixel(cub->image, pos[0], pos[1], color);
		if ((pos[0] < 0 || pos[0] >= 14 * TILE_SIZE) || (pos[1] < 0 || pos[1] >= 10 * TILE_SIZE))
		{
			return ;
		}
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

double	norm_angle(double angle)
{
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

t_intex find_vertical_intersiction(t_cube *cube, double angle)
{
    t_intex first_touch;
    t_intex next_step;
    t_intex check;

    angle = norm_angle(angle); // Normalize angle to [0, 2PI]
    // if (angle < 0)
    //     angle += 2 * M_PI;
	// printf ("angle = %f\n", 180 * angle / M_PI);

    // Calculate first vertical grid intersection
    first_touch.x = floor(cube->player->x / TILE_SIZE) * TILE_SIZE;
    if (angle < M_PI / 2 || angle > M_PI * 1.5)  // Facing right
        first_touch.x += TILE_SIZE;
    first_touch.y = fabs (cube->player->y + (cube->player->x - first_touch.x) * tan(angle));

    next_step.x = TILE_SIZE;
    if ((angle > M_PI / 2 && angle < M_PI * 1.5))  // Facing left
        next_step.x *= -1;
    next_step.y = fabs (TILE_SIZE * tan(angle));
	if (angle > M_PI && angle < 2 * M_PI)  // Facing up
		 next_step.y *= -1;
    check = first_touch;
	double x_check;

	x_check = check.x;
    // Step through grid intersections until you hit a wall
    while (check.x >= 0 && check.x < 14 * TILE_SIZE && check.y >= 0 && check.y < 10 * TILE_SIZE)
    {
		if (angle > M_PI / 2 && angle < M_PI * 1.5)
			x_check = check.x - 1;
        if (is_wall(x_check , check.y, cube))
            break;
        check.x += next_step.x;
        check.y += next_step.y;
		x_check = check.x;
    }
    return check;
}


t_intex find_horisontal_intersiction(t_cube *cube, double angle)
{
    t_intex first_touch;
    t_intex next_step;
    t_intex check;

    // Normalize the angle to be between 0 and 2PI
    angle = norm_angle(angle);
    // if (angle < 0)
    //     angle += 2 * M_PI;

    // Calculate first horizontal grid intersection (Y-axis aligned)
    first_touch.y = floor(cube->player->y / TILE_SIZE) * TILE_SIZE;
    if (angle > 0 && angle < M_PI)  // Facing downward
		first_touch.y += TILE_SIZE;
    
    first_touch.x = fabs (cube->player->x + (cube->player->y - first_touch.y) / tan(angle));

    // Y step (move to the next horizontal gridline)
    next_step.y = TILE_SIZE;
    if (!(angle > 0 && angle < M_PI))  // If facing upward
        next_step.y *= -1;

    // X step, based on angle and direction
    next_step.x = fabs (TILE_SIZE / tan(angle));
    if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
        next_step.x *= -1;

    // Step through grid intersections until we hit a wall or go out of bounds
	double y_check;

    check = first_touch;
	y_check = check.y;
    while (check.x >= 0 && check.x < 14 * TILE_SIZE && check.y >= 0 && check.y < 10 * TILE_SIZE)
    {
		if (angle > M_PI && angle < 2 * M_PI)
			y_check -= 1;
        if (is_wall(check.x, y_check, cube))  // Check for wall
            break;
        check.x += next_step.x;
        check.y += next_step.y;
		y_check = check.y;
    }
    return check;  // Return the point of intersection
}



void	ft_position(char map[10][14], double *x, double*y)
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

void	calcul_close_ray(t_intex ch, t_intex cv, t_cube *cube)
{
	double h_dis;
	double v_dis;

	h_dis = sqrt(pow(cube->player->x - ch.x, 2) + pow(cube->player->y - ch.y, 2));
	v_dis = sqrt(pow(cube->player->x - cv.x, 2) + pow(cube->player->y - cv.y, 2));
	
	if (h_dis <= v_dis)
	{
		cube->hit->x = ch.x;
		cube->hit->y = ch.y;
	}
	else
	{
		cube->hit->x = cv.x;
		cube->hit->y = cv.y;
	}
}


void ft_player(void* param)
{
    t_cube *cube = param;
    
    // Draw the player on screen (small square of pixels for visualization)
    int x, y;
    y = -2;
    while (y <= 2)
    {
        x = -2;
        while (x <= 2)
        {
            mlx_put_pixel(cube->image, cube->player->x + x, cube->player->y + y, 0xFFFA);
            x++;
        }
        y++;
    }

    // Revert back to multiple rays across the screen width (Field of View)
    double ray = cube->player->angle - (FOV_ANGLE / 2);  // Start at the left-most angle of the FOV
    t_intex ch;
    t_intex cv;

    x = -1;
    while (++x < SCREEN_WIDTH)
    {
        // Calculate both vertical and horizontal intersections for each ray
        cv = find_vertical_intersiction(cube, norm_angle (ray));
        ch = find_horisontal_intersiction(cube, norm_angle (ray));

        // Find the closest intersection (either vertical or horizontal)
        calcul_close_ray(ch, cv, cube);

        // Draw the ray to the closest intersection point
        DDA(cube->player->x, cube->player->y, cube->hit->x, cube->hit->y, cube, 502061);  // Draw each ray in the player's FOV

        // Move to the next ray by incrementing the angle based on FOV and screen width
        ray += FOV_ANGLE / SCREEN_WIDTH;
    }
}


// void ft_player(void* param)
// {
//     t_cube *cube = param;
    
//     // Draw the player on screen (small square of pixels for visualization)
//     int x, y;
//     y = -2;
//     while (y <= 2)
//     {
//         x = -2;
//         while (x <= 2)
//         {
//             mlx_put_pixel(cube->image, cube->player->x + x, cube->player->y + y, 0xFFFA);
//             x++;
//         }
//         y++;
//     }

//     // Test a single ray (adjust angle for testing)
//     // double test_angle = M_PI / 2;  // Test with a 45-degree angle, change to other angles for more tests
//     t_intex ch = find_horisontal_intersiction(cube, cube->player->angle);  // Horizontal intersection test

//     // Draw the line from the player to the horizontal intersection point
//     DDA(cube->player->x, cube->player->y, ch.x, ch.y, cube, 0xFF0000);  // Red line for horizontal test

//     // Optionally, you can also draw the vertical intersection for comparison
//     // t_intex cv = find_vertical_intersiction(cube, test_angle);  // Vertical intersection test
//     // DDA(cube->player->x, cube->player->y, cv.x, cv.y, cube, 0x00FF00);  // Green line for vertical test
// }

void ft_render(void* param)
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
            int tile_color;
            if (map[j][i] == '1')
                tile_color = 250;
            else
                tile_color = 0xFFFFFA;
            y = 0;
            while (y < TILE_SIZE - 1)
            {
				x = 0;
                while (x < TILE_SIZE - 1)
                {
                    mlx_put_pixel(cube->image, i * TILE_SIZE + x, j * TILE_SIZE + y, tile_color);
					x++;
                }
				y++;
            }
			i++;
        }
		j++;
    }
	ft_player(cube);
}

void ft_hook(mlx_key_data_t keydata, void* param)
{
	t_cube *cube = param;
	int i, j;
	i = cube->player->x / TILE_SIZE;
	j = cube->player->y / TILE_SIZE;
	int posx[2];
	int posy[2];

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
	ft_render(cube);
}

int main()
{
	t_cube		*cube;
	t_player	*player;
	t_intex		hit;

	cube = malloc(sizeof(t_cube));
	player = malloc(sizeof(t_player));
	cube->hit = &hit;
	cube->player = player;
	cube->player->angle = 0;
	if (!(cube->mlx = mlx_init(14 * TILE_SIZE, 10 * TILE_SIZE, "Cub3D", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(1);
	}
	if (!(cube->image = mlx_new_image(cube->mlx, 14 * TILE_SIZE, 10 * TILE_SIZE)))
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
	ft_position(map, &player->x, &player->y);
	mlx_loop_hook(cube->mlx, ft_render, cube);
	mlx_key_hook(cube->mlx, ft_hook, cube);
	mlx_image_to_window(cube->mlx, cube->image, 0, 0);
	mlx_loop(cube->mlx);
}
