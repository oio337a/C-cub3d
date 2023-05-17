/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:06:01 by suhwpark          #+#    #+#             */
/*   Updated: 2023/05/17 21:15:39 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_game	*init_game(void)
{
	t_game	*game;
	t_map	*map;
	// t_img	*img;

	game = (t_game *)safe_malloc(sizeof(t_game));
	map = (t_map *)safe_malloc(sizeof(t_map));
	// img = (t_img *)safe_malloc(sizeof(t_img));

	game->a = 0;
	game->d = 0;
	game->s = 0;
	game->w = 0;
	game->window = NULL;
	game->mlx = NULL;
	game->player = 0;
	map->map = NULL;
	game->map = map;
	return (game);
}