/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:49:23 by yongmipa          #+#    #+#             */
/*   Updated: 2023/05/23 16:28:02 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	exit(0);
}

static void	find_rotate(t_ray *ray, int keycode)
{
	double	olddirx;
	double	oldplanex;
	
	olddirx = ray->dirX;
	oldplanex = ray->planeX;
	if (keycode == KEY_LEFT)
	{
		ray->dirX = ray->dirX * cos(ray->rot_speed) - ray->dirY * sin(ray->rot_speed);
		ray->dirY = olddirx * sin(ray->rot_speed) + ray->dirY * cos(ray->rot_speed);
		ray->planeX = ray->planeX * cos(-ray->rot_speed) - ray->planeY * sin(ray->rot_speed);
		ray->planeY = oldplanex * sin(ray->rot_speed) + ray->planeY * cos(ray->rot_speed);
	}
	else if (keycode == KEY_RIGHT)
	{
		ray->dirX = ray->dirX * cos(-ray->rot_speed) - ray->dirY * sin(-ray->rot_speed);
		ray->dirY = olddirx * sin(-ray->rot_speed) + ray->dirY * cos(-ray->rot_speed);
		ray->planeX = ray->planeX * cos(-ray->rot_speed) - ray->planeY * sin(-ray->rot_speed);
		ray->planeY = oldplanex * sin(-ray->rot_speed) + ray->planeY * cos(-ray->rot_speed);
	}
}

int	find_move_position(t_game *game, int keycode)
{
	t_ray	*ray;

	ray = game->ray;

	if (keycode == KEY_W)
		game->info->p_pos[0]--;
	else if (keycode == KEY_A)
		game->info->p_pos[1]--;
	else if (keycode == KEY_S)
		game->info->p_pos[0]++;
	else if (keycode == KEY_D)
		game->info->p_pos[1]++;
	else if (keycode == KEY_LEFT)
		find_rotate(game->ray, keycode);
	else if (keycode == KEY_RIGHT)
		find_rotate(game->ray, keycode);
	else
		return (FALSE);
	return (TRUE);
}

static int	cant_move_forward(t_info *info, double b_pos[])
{
	if (info->map[(int)info->p_pos[0]][(int)info->p_pos[1]] == '1')
	{
		info->p_pos[0] = b_pos[0];
		info->p_pos[1] = b_pos[1];
		return (FALSE);
	}
	return (TRUE);
}

int	press_key(int keycode, t_game *game)
{
	t_info	*info;
	double		b_pos[2];

	info = game->info;
	b_pos[0] = info->p_pos[0];
	b_pos[1] = info->p_pos[1];
	if (keycode == KEY_ESC)
		exit_game(game);
	if (!find_move_position(game, keycode))
		return (0);
	if (!cant_move_forward(game->info, b_pos))
		return (0);
	else if (info->map[(int)info->p_pos[0]][(int)info->p_pos[1]] != '1')
	{
		info->map[(int)b_pos[0]][(int)b_pos[1]] = '0';
		info->map[(int)info->p_pos[0]][(int)info->p_pos[1]] = 'P';
		// printf("%d %d\n",info->p_pos[0], info->p_pos[1]);
		// draw_map(game->info, game->img, game->mlx, game->window);
	}
	return (0);
}
