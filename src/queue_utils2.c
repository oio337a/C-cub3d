/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:57:11 by suhwpark          #+#    #+#             */
/*   Updated: 2023/05/26 20:32:28 by sohyupar         ###   ########.fr       */
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
		printf("left case : %d %d\n", point->y, point->x - 1);
		visit_info->zero_cnt++; // 하나라도 올라가면 q비우고 끝낼까여?
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
		printf("right case : %d %d\n", point->y, point->x + 1);

		visit_info->zero_cnt++;
	}
}

void	visit_up(char **map, t_visit *visit_info, t_queue *queue, t_node *point)
{
	if (map[point->y - 1][point->x] == ' ')
	{
		enqueue(queue, point->x, point->y - 1);
		visit_info->visited[point->y - 1][point->x] = 1;
	}
	if (map[point->y - 1][point->x] == '0')
	{
		printf("up case : %d %d\n", point->y - 1, point->x);

		visit_info->zero_cnt++;
	}
}

void	visit_d(char **map, t_visit *visit_info, t_queue *queue, t_node *point)
{
	if (map[point->y + 1][point->x] == ' ')
	{
		enqueue(queue, point->x, point->y + 1);
		visit_info->visited[point->y + 1][point->x] = 1;
	}
	if (map[point->y + 1][point->x] == '0')
	{
		printf("down case : %d %d %c\n", point->y + 1, point->x, map[point->y + 1][point->x]);

		visit_info->zero_cnt++;
	}
}
