/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:57:11 by suhwpark          #+#    #+#             */
/*   Updated: 2023/05/17 15:47:53 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/queue.h"
#include <stdio.h>

void	visit_l(char **map, t_visit *visit_info, t_queue *queue, t_node *point)
{
	if (map[point->y][point->x - 1] == ' ')
	{
		enqueue(queue, point->x - 1, point->y);
		visit_info->visited[point->y][point->x - 1] = 1;
	}
	if (map[point->y][point->x - 1] == '0')
	{
		printf("x : %d, y : %d , c : %c\n ", (point->x - 1), (point->y), map[point->y][point->x- 1]);
		visit_info->zero_cnt++;
	}
}

void	visit_r(char **map, t_visit *visit_info, t_queue *queue, t_node *point)
{
	if (map[point->y][point->x + 1] == ' ')
	{
		enqueue(queue, point->x + 1, point->y);
		visit_info->visited[point->y][point->x + 1] = 1;
	}
	if (map[point->y][point->x + 1] == '0')
	{
		printf("x : %d, y : %d, c : %c\n ", (point->x - 1), (point->y), map[point->y][point->x- 1]);
		visit_info->zero_cnt++;
	}
}

void	visit_d(char **map, t_visit *visit_info, t_queue *queue, t_node *point)
{
	if (map[point->y - 1][point->x] == ' ')
	{
		enqueue(queue, point->x, point->y - 1);
		visit_info->visited[point->y - 1][point->x] = 1;
	}
	if (map[point->y - 1][point->x] == '0')
	{
		printf("x : %d, y : %d, c : %c\n ", (point->x), (point->y- 1), map[point->y - 1][point->x]);
		visit_info->zero_cnt++;
	}
}

void	visit_up(char **map, t_visit *visit_info, t_queue *queue, t_node *point)
{
	if (map[point->y + 1][point->x] == ' ')
	{
		enqueue(queue, point->x, point->y + 1);
		visit_info->visited[point->y + 1][point->x] = 1;
	}
	if (map[point->y + 1][point->x] == '0')
	{
		printf("x : %d, y : %d, c : %c\n ", (point->x), (point->y + 1), map[point->y + 1][point->x]);
		visit_info->zero_cnt++;
	}
}