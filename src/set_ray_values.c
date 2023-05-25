/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ray_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:10:20 by suhwpark          #+#    #+#             */
/*   Updated: 2023/05/25 20:57:19 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	set_ray_values(t_game *game, int x)
{
	t_ray	*ray;

	ray = game->ray;
	ray->map_x = (int)game->info->p_pos[1];
	ray->map_y = (int)game->info->p_pos[0];
	ray = game->ray;
	ray->cameraX = 2 * x / (double)W - 1;
	ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
	ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);
	ray->hit = 0;
}

void	set_side_dist(t_game *game)
{
	t_ray	*ray;

	ray = game->ray;
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (game->info->p_pos[1] - ray->map_x) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->map_x + 1.0 - game->info->p_pos[1])
			* ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->info->p_pos[0] - ray->map_y) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->map_y + 1.0 - game->info->p_pos[0])
			* ray->deltaDistY;
	}
}

void	set_draw_values(t_game *game)
{
	t_ray	*ray;

	ray = game->ray;
	if (ray->side == 0)
	{
		ray->perpWallDist = ((ray->map_x - game->info->p_pos[1])
				+ (1 - ray->stepX) / 2) / ray->rayDirX;
	}
	else
	{
		ray->perpWallDist = ((ray->map_y - game->info->p_pos[0])
				+ (1 - ray->stepY) / 2) / ray->rayDirY;
	}
	ray->line_height = (int)(H / ray->perpWallDist);
	ray->draw_start = -ray->line_height / 2 + H / 2 ;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = H / 2 + (ray->line_height / 2);
	if (ray->draw_end >= H)
		ray->draw_end = H - 1;
}

void	set_wall_values(t_game *game)
{
	t_ray	*ray;
	t_wall	*wall;

	ray = game->ray;
	wall = game->wall;
	if (ray->side == 0)
		wall->wall_x = game->info->p_pos[0] + ray->perpWallDist * ray->rayDirY;
	else
		wall->wall_x = game->info->p_pos[1] + ray->perpWallDist * ray->rayDirX;
	wall->wall_x -= floor(wall->wall_x);
	wall->tex_x = (int)(wall->wall_x * (double)64);
	if (ray->side == 0 && ray->rayDirX > 0)
		wall->tex_x = 64 - wall->tex_x - 1;
	if (ray->side == 1 && ray->rayDirY < 0)
		wall->tex_x = 64 - wall->tex_x - 1;
	wall->step = 1.0 * 64 / ray->line_height;
	wall->tex_pos = (ray->draw_start - H / 2 + ray->line_height / 2)
		* wall->step;
}

void	set_colors_values(t_game *game, int x)
{
	t_ray	*ray;
	t_wall	*wall;
	int		y;

	ray = game->ray;
	wall = game->wall;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		wall->tex_y = (int)wall->tex_pos & (64 - 1);
		wall->tex_pos += wall->step;
		if (ray->side == 0 && ray->rayDirX > 0)
			ray->color = ray->texture[3][wall->tex_y * 64 + wall->tex_x];
		else if (ray->side == 0 && ray->rayDirX < 0)
			ray->color = ray->texture[2][wall->tex_y * 64 + wall->tex_x];
		else if (ray->side == 1 && ray->rayDirY > 0)
			ray->color = ray->texture[0][wall->tex_y * 64 + wall->tex_x];
		else if (ray->side == 1 && ray->rayDirY < 0)
			ray->color = ray->texture[1][wall->tex_y * 64 + wall->tex_x];
		ray->buf[y][x] = ray->color;
		y++;
	}
}
