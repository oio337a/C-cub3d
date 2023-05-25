/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ray_values2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:25:58 by suhwpark          #+#    #+#             */
/*   Updated: 2023/05/25 20:55:14 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	set_hit_values(t_game *game)
{
	t_ray	*ray;

	ray = game->ray;
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->map_x += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->map_y += ray->stepY;
			ray->side = 1;
		}
		if (game->info->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	set_textures_values(t_game *game)
{
	set_draw_values(game);
	set_wall_values(game);
}
