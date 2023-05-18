/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:19:07 by yongmipa          #+#    #+#             */
/*   Updated: 2023/05/18 21:16:18 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include "../mlx/mlx.h"

int	word_cnt(char const *s)
{
	int	cnt;

	cnt = 0;
	while (*s)
	{
		while (*s && ft_isspace(*s) == 1)
			s++;
		if (*s && ft_isspace(*s) == 0)
		{
			cnt++;
			while (*s && ft_isspace(*s) == 0)
				s++;
		}
	}
	return (cnt);
}

int	word_len(char const *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]) == 0)
		i++;
	return (i);
}

char	*is_strdup(const char *s, int size)
{
	int		i;
	char	*dst;

	i = 0;
	dst = (char *)malloc(sizeof(char) * (size + 1));
	if (!dst)
		return (0);
	while (s[i] && i < size)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

// 혹시 필요하면..?
//char	**freeall(char **str, int cnt)
//{
//	int	i;
//
//	i = 0;
//	while (i < cnt)
//		free(str[i++]);
//	free(str);
//	return (0);
//}

char	**is_split(char const *s)
{
	char	**dest;
	int		cnt;
	int		i;
	int		len;

	i = 0;
	cnt = word_cnt(s);
	dest = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!dest)
		ft_err("malloc");
	while (i < cnt)
	{
		while (*s && ft_isspace(*s) == 1)
			s++;
		len = word_len(s);
		dest[i] = is_strdup(s, len);
		if (!dest[i])
			ft_err("malloc");
		s += len;
		i++;
	}
	dest[i] = 0;
	return (dest);
}

int	cnt_info_flag(t_game *game)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (i < 6)
	{
		if (game->info->info_flag[i] > 1)
			ft_err("Duplicate information");
		if (game->info->info_flag[i] == 1)
			cnt++;
		i++;
	}
	return (cnt);
}

char	*read_file(int fd, t_game *game)
{
	char	*line;
	char	*join;
	char	*tmp;

	join = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (cnt_info_flag(game) == 6)
		{
			tmp = join;
			join = ft_strjoin(join, line);
			free(tmp);
		}
		else
			read_map_info(line, game);
		free(line);
	}
	return (join);
}

static void	init_texture(char **str, t_game *game, int type)
{
	int	w;
	int	h;

	if (ft_size(str) != 2)
		ft_err("information error");
	if (type == 1)
	{
		game->img->north = mlx_xpm_file_to_image(game->mlx, str[1], &w, &h);
		game->info->info_flag[0]++;
	}
	else if (type == 2)
	{
		game->img->south = mlx_xpm_file_to_image(game->mlx, str[1], &w, &h);
		game->info->info_flag[1]++;
	}
	else if (type == 3)
	{
		game->img->west = mlx_xpm_file_to_image(game->mlx, str[1], &w, &h);
		game->info->info_flag[2]++;
	}
	else if (type == 4)
	{
		game->img->east = mlx_xpm_file_to_image(game->mlx, str[1], &w, &h);
		game->info->info_flag[3]++;
	}
}

//rgc 요소사이에 공백 안들어오게 처리
//atoi에서 +,-부호 한개씩만 있을때도 처리해주기 ->아토이 일단 주석처리하고 제것 넣어놨어요.
static void	check_color(int *map_info, char **color)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		map_info[i] = ft_atoi(color[i]);
		if (map_info[i] < 0 || 255 < map_info[i])
			ft_err("Color range (0 ~ 255)");
		i++;
	}
}

static void	init_color(char **str, t_game *game, int type)
{
	char	**color;

	if (ft_size(str) != 2)
		ft_err("information error");
	color = ft_split(str[1], ',');
	if (ft_size(color) != 3)
		ft_err("we need 3 color");
	if (type == 5)
	{
		game->info->info_flag[4]++;
		check_color(game->info->f, color);
	}
	else
	{
		game->info->info_flag[5]++;
		check_color(game->info->c, color);
	}
	ft_free(color);
}

//texture, color segmentation fault ->구조체 수정
int	read_map_info(char *str, t_game *game)
{
	char	**temp;

	temp = is_split(str);
	if (temp[0])
	{
		if (!ft_strncmp(temp[0], "NO", 3))
			init_texture(temp, game, 1);
		else if (!ft_strncmp(temp[0], "SO", 3))
			init_texture(temp, game, 2);
		else if (!ft_strncmp(temp[0], "WE", 3))
			init_texture(temp, game, 3);
		else if (!ft_strncmp(temp[0], "EA", 3))
			init_texture(temp, game, 4);
		else if (!ft_strncmp(temp[0], "F", 2))
			init_color(temp, game, 5);
		else if (!ft_strncmp(temp[0], "C", 2))
			init_color(temp, game, 6);
		else
		{
			ft_free(temp);
			ft_err("map info error");
		}
	}
	ft_free(temp);
	return (0);
}
