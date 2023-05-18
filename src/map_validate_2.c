/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:35:04 by yongmipa          #+#    #+#             */
/*   Updated: 2023/05/18 19:32:37 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	ft_str_col(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	is_whitespace(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}

int	start_end_wall(char *map)
{
	int	i;

	i = is_whitespace(map);
	while (map[i])
	{
		if (map[i] != '1' && map[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	context_check(char context, t_game *dir, int x, int y)
{
	if (context != '0' && context != '1' && context != 'W' \
		&& context != 'S' && context != 'E' && context != 'N' \
		&& context != ' ')
		return (FALSE);
	if (context == 'W')
	{
		dir->info->w++;
		dir->info->p_pos[0] = y;
		dir->info->p_pos[1] = x;
		dir->info->player++;
	}
	else if (context == 'E')
	{
		dir->info->e++;
		dir->info->p_pos[0] = y;
		dir->info->p_pos[1] = x;
		dir->info->player++;
	}
	else if (context == 'S')
	{
		dir->info->s++;
		dir->info->p_pos[0] = y;
		dir->info->p_pos[1] = x;
		dir->info->player++;
	}
	else if (context == 'N')
	{
		dir->info->n++;
		dir->info->p_pos[0] = y;
		dir->info->p_pos[1] = x;
		dir->info->player++;
	}
	return (TRUE);
}

int	is_player_space(t_game *dir, char **map)
{
	if (map[dir->info->p_pos[0] - 1][dir->info->p_pos[1]] == ' ')
		return (FALSE);
	if (map[dir->info->p_pos[0] + 1][dir->info->p_pos[1]] == ' ')
		return (FALSE);
	if (map[dir->info->p_pos[0]][dir->info->p_pos[1] - 1] == ' ')
		return (FALSE);
	if (map[dir->info->p_pos[0]][dir->info->p_pos[1] + 1] == ' ')
		return (FALSE);
	return (TRUE);
}

int	check_wall(char *map, int len)
{
	int	i;

	i = is_whitespace(map);
	if (map[i] == '1' || map[len - 1] != '1')
		return (TRUE);
	return (FALSE);
}

int	all_around_wall(char **map)
{
	int	i;
	int	len;

	i = 0;
	len = ft_str_col(map);
	while (map[i])
	{
		if (i == 0 || i == len - 1)
		{
			if (start_end_wall(map[i]) == FALSE)
				return (FALSE);
		}
		else
		{
			if (check_wall(map[i], ft_strlen(map[i])) == FALSE)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	mid_context_check(char **map, t_game *dir)
{
	int	i;
	int	j;
	int	col;

	col = ft_str_col(map);
	i = 1;
	while (map[i] && i < col)
	{
		j = 0;
		while (map[i][j])
		{
			if (context_check(map[i][j], dir, j, i) == FALSE)
				return (-1);
			j++;
		}
		i++;
	}
	if (dir->info->player != 1)
	{
		ft_err("player count err\n");
		return (-1);
	}
	return (1);
}

int	over_len(char **map)
{
	int	prev_len;
	int	curr_len;
	int	i;

	prev_len = ft_strlen(map[0]);
	curr_len = 0;
	i = 0;
	while (map[i])
	{
		curr_len = ft_strlen(map[i]);
		if (curr_len > prev_len)
		{
			while (map[i][prev_len])
			{
				if (map[i][prev_len] != ' ' && map[i][prev_len] != '1')
					return (FALSE);
				prev_len++;
			}
		}
		prev_len = ft_strlen(map[i]);
		i++;
	}
	return (TRUE);
}

int	validate_all(char *map_join, t_game *game)
{
	char	**map;

	printf("before split\n");
	map = ft_split2(map_join, '\n');
	printf("after split\n");
	int i = 0;
	printf("map start\n");
	while(map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	if (!map)
		return (FALSE);
	if (bfs(map) == TRUE && over_len(map) == TRUE
		&& all_around_wall(map) == TRUE && mid_context_check(map, game) == TRUE && is_player_space(game, map) == TRUE)
	{
		game->info->map = map;
		return (TRUE);
	}
	ft_free(map);
	return (FALSE);
}
