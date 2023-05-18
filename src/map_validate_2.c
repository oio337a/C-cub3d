/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:35:04 by yongmipa          #+#    #+#             */
/*   Updated: 2023/05/18 17:20:50 by sohyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
// 여기서 맵 context에 대한 검수를 하면 될거같아요
/*
맵 파싱
2. 벽에 다 둘러 싸이게
2. cub 파일의 마지막에 위치하도록 -> 맵 마지막줄 뒤에 EOF 검수?
3. 제시된 콘텐츠 외에 다른게 들어오면 안됨
4. 제시된 콘텐츠가 부족해도 안됨 벽과 벽을 제외한 콘텐츠에서 공백 안됨
5. 직사각형이 아닌 맵 1 검수 -> whitespace가 아닌 문자를 처음 만났을 때 1, 개행 전에 1인지?
*/

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
		if (map[i] != '1' && !ft_isspace(map[i]))
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

int	all_around_wall(char **map) // 이차원이라 생각할게여
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

	// 플레이어가 있는지에 대한 판단여부만 해주면 끝!
	// 추가적으로 맵 끝났는데 엔터나 헛소리 들어오는거 봐야댐?

// int main()
// {
// 	int fd;
// 	char *file = "test.txt";
// 	fd = open(file, O_RDONLY);
// 	char *join = ft_strdup("");
// 	char *line;
// 	t_game *a;
// 	a = (t_game *)malloc(sizeof(t_game));
// 	ft_memset(a, 0, sizeof(a));
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		join = ft_strjoin(join, line);
// 		free(line);
// 	}
// 	// char **map = ft_split(join, '\n');
// 	// int i = 0;
// 	// while(map[i])
// 	// {
// 	// 	printf("map : %s\n", map[i]);
// 	// 	i++;
// 	// }
// 	int qqq = validate_all(join, a);
// 	printf("validate : %d\n", qqq);
// 	printf("%d %d %d %d %d %d\n", a->p_pos[0], a->p_pos[1], a->a, a->d, a->s, a->w);
// 	// printf("all _Wall : %d\n", all_around_wall(map));
// }
