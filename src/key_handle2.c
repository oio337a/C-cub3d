/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:23:04 by suhwpark          #+#    #+#             */
/*   Updated: 2023/05/25 21:36:40 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	exit(0);
}

void	find_rotate_left(t_ray *ray)
{
	double	olddirx;
	double	oldplanex;

	olddirx = ray->dirX;
	oldplanex = ray->planeX;
	ray->dirX = ray->dirX * cos(ray->rot_speed) \
				- ray->dirY * sin(ray->rot_speed);
	ray->dirY = olddirx * sin(ray->rot_speed) \
				+ ray->dirY * cos(ray->rot_speed);
	ray->planeX = ray->planeX * cos(-ray->rot_speed) \
				- ray->planeY * sin(ray->rot_speed);
	ray->planeY = oldplanex * sin(ray->rot_speed) \
				+ ray->planeY * cos(ray->rot_speed);
}

void	find_rotate_right(t_ray *ray)
{
	double	olddirx;
	double	oldplanex;

	olddirx = ray->dirX;
	oldplanex = ray->planeX;
	ray->dirX = ray->dirX * cos(-ray->rot_speed) \
				- ray->dirY * sin(-ray->rot_speed);
	ray->dirY = olddirx * sin(-ray->rot_speed) \
				+ ray->dirY * cos(-ray->rot_speed);
	ray->planeX = ray->planeX * cos(-ray->rot_speed) \
				- ray->planeY * sin(-ray->rot_speed);
	ray->planeY = oldplanex * sin(-ray->rot_speed) \
				+ ray->planeY * cos(-ray->rot_speed);
}

void	find_move_position(t_game *game, int keycode)
{
	t_ray	*ray;

	ray = game->ray;
	if (keycode == K_W)
	{
		if (cant_move_forward(game->info, 0, ray->dirX * ray->move_speed))
			game->info->p_pos[1] += ray->dirX * ray->move_speed;
		if (cant_move_forward(game->info, ray->dirY * ray->move_speed, 0))
			game->info->p_pos[0] += ray->dirY * ray->move_speed;
	}
	else if (keycode == K_S)
	{
		if (cant_move_forward(game->info, 0, -(ray->dirX * ray->move_speed)))
			game->info->p_pos[1] -= ray->dirX * ray->move_speed;
		if (cant_move_forward(game->info, -(ray->dirY * ray->move_speed), 0))
			game->info->p_pos[0] -= ray->dirY * ray->move_speed;
	}
	else if (keycode == K_A)
	{
		if (cant_move_forward(game->info, 0, -(ray->dirY * ray->move_speed)))
			game->info->p_pos[1] -= ray->dirY * ray->move_speed;
		if (cant_move_forward(game->info, ray->dirY * ray->move_speed, 0))
			game->info->p_pos[0] += ray->dirX * ray->move_speed;
	}
	else if (keycode == K_D)
	{
		if (cant_move_forward(game->info, 0, ray->dirY * ray->move_speed))
			game->info->p_pos[1] += ray->dirY * ray->move_speed;
		if (cant_move_forward(game->info, -(ray->dirY * ray->move_speed), 0))
			game->info->p_pos[0] -= ray->dirX * ray->move_speed;
	}
}
