/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:35:04 by yongmipa          #+#    #+#             */
/*   Updated: 2023/05/25 22:24:00 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	validate_all(char *map_join, t_game *game)
{
	char	**map;

	if (!game->img->north || !game->img->south
		|| !game->img->east || !game->img->west)
	{
		free(map_join);
		ft_err("image path", game);
	}
	map = ft_split2(map_join, '\n');
	if (!map)
		return (FALSE);
	if (bfs(map) && overlen_check(map) && all_around_wall(map)
		&& mid_context_check(map, game) && is_player_space(game, map))
	{
		free(map_join);
		game->info->map = map;
		return (TRUE);
	}
	free(map_join);
	ft_free(map);
	return (FALSE);
}
