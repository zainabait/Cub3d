/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:25:27 by zait-bel          #+#    #+#             */
/*   Updated: 2024/10/13 13:19:58 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

t_inter	find_vertical_intersection(t_cube *cube, double angle)
{
	t_inter	first_touch;
	t_inter	next_step;
	t_inter	check;

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