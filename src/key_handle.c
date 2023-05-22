/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:49:23 by yongmipa          #+#    #+#             */
/*   Updated: 2023/05/22 15:33:44 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	exit(0);
}

static size_t	find_move_position(t_info *info, int keycode)
{
	// 이게 맞는지 몰겠음.
	size_t	i;

	if (keycode == KEY_W)
		i = info->p_pos[0] - 1;
	else if (keycode == KEY_A)
		i = info->p_pos[1] - 1;
	else if (keycode == KEY_S)
		i = info->p_pos[0] + 1;
	else if (keycode == KEY_D)
		i = info->p_pos[1] + 1;
	/*
	else if (keycode == KEY_LEFT)
		raycast();
	else if (keycode == KEY_RIGHT)
		raycast();
	*/
	else
		i = INVALID_KEYCODE;
	return (i);
}


int	press_key(int keycode, t_game *game)
{
	t_info	*info;
	size_t	i;
	size_t	j;

	if (keycode == KEY_ESC)
		exit_game(game);
	info = game->info;
	i = find_move_position(info, keycode);
	j = find_move_position(info, keycode);
	printf("i: %zu j: %zu\n", i, j);
	if (i == INVALID_KEYCODE)
		return (0);
	else if (info->map[i][j] != '1')
	{
		info->map[info->p_pos[0]][info->p_pos[1]] = '0';
		info->map[i][j] = 'P';
		info->p_pos[0] = i;
		info->p_pos[1] = j;
		// draw_map(game->info, game->img, game->mlx, game->window);
	}
	return (0);
}
