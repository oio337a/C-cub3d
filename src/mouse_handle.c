/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 01:53:19 by hyecheon          #+#    #+#             */
/*   Updated: 2023/05/29 01:53:19 by hyecheon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	mouse_right(t_ray *ray)
{
	double	olddirx;
	double	oldplanex;

	olddirx = ray->dir_x;
	oldplanex = ray->plane_x;
	ray->dir_x = ray->dir_x * cos(-ray->rot_speed) \
				- ray->dir_y * sin(-ray->rot_speed);
	ray->dir_y = olddirx * sin(-ray->rot_speed) \
				+ ray->dir_y * cos(-ray->rot_speed);
	ray->plane_x = ray->plane_x * cos(-ray->rot_speed) \
				- ray->plane_y * sin(-ray->rot_speed);
	ray->plane_y = oldplanex * sin(-ray->rot_speed) \
				+ ray->plane_y * cos(-ray->rot_speed);
}

static void	mouse_left(t_ray *ray)
{
	double	olddirx;
	double	oldplanex;

	olddirx = ray->dir_x;
	oldplanex = ray->plane_x;
	ray->dir_x = ray->dir_x * cos(ray->rot_speed) \
						- ray->dir_y * sin(ray->rot_speed);
	ray->dir_y = olddirx * sin(ray->rot_speed) \
						+ ray->dir_y * cos(ray->rot_speed);
	ray->plane_x = ray->plane_x * cos(ray->rot_speed) \
						- ray->plane_y * sin(ray->rot_speed);
	ray->plane_y = oldplanex * sin(ray->rot_speed) \
						+ ray->plane_y * cos(ray->rot_speed);
}

int	mouse_handle(int x, int y, t_ray *ray)
{
	if (y > 0 && y < H)
	{
		if (0 < x && x < (W / 6))
			mouse_left(ray);
		else if (W - (W / 6) < x && x < W)
			mouse_right(ray);
	}
	return (0);
}
