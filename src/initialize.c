/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:06:01 by suhwpark          #+#    #+#             */
/*   Updated: 2023/05/19 14:03:24 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include "../mlx/mlx.h"

static void	initialize_array(int arr[], int len)
{
	int	i;

	i = -1;
	while (++i < len)
		arr[i] = 0;
}

t_game	*init_game(void)
{
	t_game	*game;
	t_info	*info;
	t_img	*img;

	game = (t_game *)safe_malloc(sizeof(t_game));
	info = (t_info *)safe_malloc(sizeof(t_info));
	img = (t_img *)safe_malloc(sizeof(t_img));
	info->e = 0;
	info->n = 0;
	info->s = 0;
	info->w = 0;
	initialize_array(info->info_flag, 6);
	initialize_array(info->p_pos, 2);
	initialize_array(info->c, 3);
	initialize_array(info->f, 3);
	game->window = NULL;
	game->mlx = NULL;
	info->player = 0;
	info->map = NULL;
	img->east = NULL;
	img->west = NULL;
	img->north = NULL;
	img->south = NULL;
	game->info = info;
	game->img = img;
	game->mlx = mlx_init();
	return (game);
}
