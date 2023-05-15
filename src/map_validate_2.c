/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:35:04 by yongmipa          #+#    #+#             */
/*   Updated: 2023/05/15 21:44:29 by suhwpark         ###   ########.fr       */
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
	int i;

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

int	whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	start_end_wall(char *map)
{
	//1 아니면 스페이스바 외에 다른게 들어오면 안됨 추가적으로 len 맞춰바야댐?
	int	i;

	i = is_whitespace(map);
	while (map[i++])
		if (map[i] != '1' && map[i] != ' ')
			return(-1);
	return (1);
}

int	check_wall(char *map, int len)
{
	int	i;
	
	i = is_whitespace(map);
	if (map[i] != 1 || map[len - 1] != 1) // 양 끝부분 1로 돼있음?
		return (-1);
	return(1);
}

// 추가적으로 맵 중간에 빈줄이 있으면 안되게 -> 얘는 gnl 총 라인 개수랑 
// validation 후의 개수를 비교해야될거같은데 어덕?????
// gnl을 변형시켜야되나여

int	all_around_wall(char **map) // 이차원이라 생각할게여
{
	int i;
	int	len;

	i = 0;
	len = ft_str_col(map);
	while (map[i])
	{
		if (i == 0 || i == len)
		{
			if (start_end_wall(map[i]) == -1)
			{
				ft_free(map);
				return (-1);
			}
		}
		else
		{
			if (check_wall(map[i], ft_strlen(map[i])) == -1)
			{
				ft_free(map);
				return (-1);
			}
		}
	}
	return (1);
}

// int	context_check(char context, t_game *dir)
// {
// 	if (context != '0' && context != '1' && context != 'W' \
// 		&& context != 'S' && context != 'A' && context != 'D' \
// 		&& !whitespace(context))
// 		return (-1);
// 	if (context == 'W')
// 		dir->w++;
// 	else if (context == 'A')
// 		dir->a++;
// 	else if (context == 'S')
// 		dir->s++;
// 	else if (context == 'D')
// 		dir->d++;
// 	if (dir->w >= 2 || dir->a >= 2 || dir->s >= 2 || dir->d >= 2)
// 	{
// 		ft_err("player count err\n");
// 		return (-1);
// 	}
// 	return (1);
// }

// int	mid_context_check(char **map, t_game *dir) //WASD, 1, 0만 있어야댐
// {
// 	int	i;
// 	int	j;
// 	int	col;

// 	col = ft_str_col(map);
// 	i = 1;
// 	while (map[i] && i < col)
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
// 			if (context_check(map[i][j], dir) == -1)
// 			{
// 				ft_free(map);
// 				return (-1);
// 			}
// 		}
// 		i++;
// 	}
// 	if (dir->w == 0 && dir->a == 0 && dir->s == 0 && dir->d == 0)
// 	{
// 		ft_free(map);
// 		ft_err("player count err\n");
// 		return (-1);
// 	}
// 	return (1);
// }

void	append_space_index(char **map, t_queue *q)
{
	int i;
	int j;

	i = 0;
	printf("asdasd\n");
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
			{
				printf("i: %d j: %d\n", i, j);
				enqueue(q, j, i);
			}
			j++;
		}
		i++;
	}
}

static int	ft_strlen2(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int	bfs_test(char **map)
{
	// int	**visited;
	int	i;
	int	j;
	t_visit	*visit;
	t_queue *q;
	t_node *pop;

	i = 0;
	visit = (t_visit *)malloc(sizeof(t_visit));
	visit->visited = (int **)malloc(sizeof(int *) * (ft_str_col(map) + 1));
	if (!visit->visited)
		return (-1);
	printf("%d\n", ft_str_col(map));
	while (map[i])
	{
		j = ft_strlen(map[i]);
		visit->visited[i] = (int *)ft_calloc(sizeof(int), j);
		if (!visit->visited[i])
			return (-1);
		i++;
	}
	visit->visited[i] = NULL;
	visit->zero_cnt = 0;
	q = init_queue();
	append_space_index(map, q);
	while (!is_empty(q))
	{
		pop = dequeue(q);
		// printf("pos x: %d pox y : %d\n", pop->x, pop->y);
		if (pop->x - 1 >= 0)
			if (visit->visited[pop->y][pop->x - 1] == 0)
				visit_left(map, visit, q, pop);
		if (pop->x + 1 < ft_strlen2(map[pop->y]))
			if (visit->visited[pop->y][pop->x + 1] == 0)
				visit_right(map, visit, q, pop);
		if (pop->y - 1 >= 0)
			if (visit->visited[pop->y - 1][pop->x] == 0)
				visit_down(map, visit, q, pop);
		if (pop->y + 1 < ft_str_col(map))
			if (visit->visited[pop->y + 1][pop->x] == 0)
				visit_up(map, visit, q, pop);
		free(pop);
	}
	if (visit->zero_cnt != 0)
		return (-1);
	// printf("zero count : %d\n", visit->zero_cnt);
	return (1);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

int main()
{
	int fd;
	char *file = "test.txt";
	fd = open(file, O_RDONLY);
	char *join = ft_strdup("");
	char *line;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		join = ft_strjoin(join, line);
		free(line);
	}
	char **map = ft_split(join, '\n');
	int i = 0;
	while(map[i])
	{
		printf("map : %s\n", map[i]);
		i++;
	}
	int a = bfs_test(map);
	printf("%d\n", a);
}