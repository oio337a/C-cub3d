/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:35:04 by yongmipa          #+#    #+#             */
/*   Updated: 2023/05/26 15:39:43 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	img_check(char *map_join, t_game *game)
{
	if (!game->img->north || !game->img->south
		|| !game->img->east || !game->img->west)
	{
		free(map_join);
		ft_err("image path", game);
	}
}

int	validate_all(char *map_join, t_game *game)
{
	char	**map;

	img_check(map_join, game);
	if (!*map_join)
	{
		free(map_join);
		return (FALSE);
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
	printf("after split???\n");
	free(map_join);
	ft_free(map);
	return (FALSE);
}
