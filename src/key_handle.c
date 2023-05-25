/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:49:23 by yongmipa          #+#    #+#             */
/*   Updated: 2023/05/25 22:35:09 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	find_move(t_game *game, int keycode)
{
	if (keycode == K_L)
		find_rotate_left(game->ray);
	else if (keycode == K_R)
		find_rotate_right(game->ray);
	else if (keycode == K_W || keycode == K_S || \
	keycode == K_A || keycode == K_D)
		find_move_position(game, keycode);
	else
		return (FALSE);
	return (TRUE);
}

int	cant_move_forward(t_info *info, double y, double x)
{
	double	move;

	move = 0.05;
	if (info->map[(int)(info->p_pos[0] + y)][(int)(info->p_pos[1] + x)] == '1')
		return (FALSE);
	else if (info->map[(int)(info->p_pos[0] + y + move)][(int)(info->p_pos[1] + x)] == '1')
		return (FALSE);
	else if (info->map[(int)(info->p_pos[0] + y)][(int)(info->p_pos[1] + x + move)] == '1')
		return (FALSE);
	else if (info->map[(int)(info->p_pos[0] + y - move)][(int)(info->p_pos[1] + x)] == '1')
		return (FALSE);
	else if (info->map[(int)(info->p_pos[0] + y)][(int)(info->p_pos[1] + x - move)] == '1')
		return (FALSE);
	else if (info->map[(int)(info->p_pos[0] + y + move)][(int)(info->p_pos[1] + x - move)] == '1')
		return (FALSE);
	else if (info->map[(int)(info->p_pos[0] + y + move)][(int)(info->p_pos[1] + x + move)] == '1')
		return (FALSE);
	else if (info->map[(int)(info->p_pos[0] + y - move)][(int)(info->p_pos[1] + x + move)] == '1')
		return (FALSE);
	else if (info->map[(int)(info->p_pos[0] + y - move)][(int)(info->p_pos[1] + x - move)] == '1')
		return (FALSE);
	return (TRUE);
}

int	press_key(int keycode, t_game *game)
{
	t_info		*info;
	double		b_pos[2];

	info = game->info;
	b_pos[0] = info->p_pos[0];
	b_pos[1] = info->p_pos[1];
	if (keycode == K_ESC)
		exit_game(game);
	if (!find_move(game, keycode))
		return (0);
	if (info->map[(int)info->p_pos[0]][(int)info->p_pos[1]] != '1')
		info->map[(int)b_pos[0]][(int)b_pos[1]] = '0';
	return (0);
}
