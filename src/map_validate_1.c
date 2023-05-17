/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:19:07 by yongmipa          #+#    #+#             */
/*   Updated: 2023/05/17 18:02:33 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
char	**freeall(char **str, int cnt)
{
	int	i;

	i = 0;
	while (i < cnt)
		free(str[i++]);
	free(str);
	return (0);
}

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
		if (game->info_flag[i] > 1)
			ft_err("Duplicate information\n");
		if (game->info_flag[i] == 1)
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
			//join전에 맵 아닌 부분 없애고 보내주는것 만들지 고민....!
			tmp = join;
			join = ft_strjoin(join, line);
			free(tmp);
		}
		else
			read_map_info(line, game);
		free(line);
	}
	printf("%s\n", join);
	return (join);
}

static void	init_texture(char **str, t_game *game, int type)
{
	if (ft_size(str) != 2)
		ft_err("information error\n");
	//일단 mlx연결 전이라 테스트를 위해 img구조체 char *로 바꿨습니다.
	if (type == 1)
	{
		// mlx_xpm_file_to_image 로 이어줘야하는지 몰겠음...
		game->img->north = str[1];
		game->info_flag[0]++;
	}
	else if (type == 2)
	{
		game->img->south = str[1];
		game->info_flag[1]++;
	}
	else if (type == 3)
	{
		game->img->west = str[1];
		game->info_flag[2]++;
	}
	else if (type == 4)
	{
		game->img->east = str[1];
		game->info_flag[3]++;
	}
}

//rgb 값 16진수로 바꿔주는 함수 만들고 값 담아주기

static void	init_color(char **str, t_game *game, int type)
{
	char	**color;

	if (ft_size(str) != 2)
		ft_err("information error\n");
	color = ft_split(str[1], ',');
	if (ft_size(color) != 3)
		ft_err("we need 3 color\n");
	//rgc 요소사이에 공백 안들어오게 처리
	//atoi에서 +,-부호 한개씩만 있을때도 처리해주기 ->아토이 일단 주석처리하고 제것 넣어놨어요.
	//줄수 줄이기 위해 일단 변수 지웠음...
	// 255 넘어가는지 체크 해야함~~!!!!!
	if (ft_atoi(color[0]) == -1 || ft_atoi(color[1]) == -1 || \
	ft_atoi(color[2]) == -1)
		ft_err("Color range (0 ~ 255)\n");
	if (type == 5)
	{
		game->info_flag[4]++;
		game->map.f[0] = ft_atoi(color[0]);
		game->map.f[1] = ft_atoi(color[1]);
		game->map.f[2] = ft_atoi(color[2]);
	}
	else
	{
		game->info_flag[5]++;
		game->map.c[0] = ft_atoi(color[0]);
		game->map.c[1] = ft_atoi(color[1]);
		game->map.c[2] = ft_atoi(color[2]);
	}
	ft_free(color);
}

int	read_map_info(char *str, t_game *game)
{
	char	**temp;

	temp = is_split(str);
	if (!temp[0])
		return (0);
	printf("%s %s\n", temp[0], temp[1]);
	//이 부분에서 segmentation fault ->구조체 수정
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
		ft_err("map info error\n");
	}
	ft_free(temp);
	return (0);
}
