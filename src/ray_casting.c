/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:45:10 by suhwpark          #+#    #+#             */
/*   Updated: 2023/05/25 21:28:18 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

	// floor->DirX0 = game->ray->dirX - game->ray->planeX;
	// floor->DirY0 = game->ray->dirY - game->ray->planeY;
	// floor->DirX1 = game->ray->dirX + game->ray->planeX;
	// floor->DirY1 = game->ray->dirY + game->ray->planeY;
	// floor->rowDist = (float)(0.5 * H) / (int)(y - (H / 2));
	// floor->floorStepX = floor->rowDist * (floor->DirX1 - floor->DirX0) / W;
	// floor->floorStepY = floor->rowDist * (floor->DirY1 - floor->DirY0) / W;
	// floor->floorX = game->info->p_pos[1] + floor->rowDist * floor->DirX0;
	// floor->floorY = game->info->p_pos[0] + floor->rowDist * floor->DirY0;

void	floor_casting(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (y < H)
	{

		x = 0;
		while (x < W)
		{
			game->ray->buf[y][x] = 0xFF0000;
			game->ray->buf[H - y - 1][x] = 0x00FF00;
			x++;
		}
		y++;
	}
}

void	wall_casting(t_game *game)
{
	int		x;

	x = 0;
	while (x < W)
	{
		set_ray_values(game, x);
		set_side_dist(game);
		set_hit_values(game);
		set_textures_values(game);
		set_colors_values(game, x);
		x++;
	}
}
