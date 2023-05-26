/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:06:01 by suhwpark          #+#    #+#             */
/*   Updated: 2023/05/26 14:46:41 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static t_ray	*init_ray(void)
{
	t_ray	*ray;

	ray = (t_ray *)safe_malloc(sizeof(t_ray));
	ft_memset(ray, 0, sizeof(t_ray));
	// ray->planeX = 0.0;
	// ray->planeY = 0.66;
	ray->move_speed = 0.05;
	ray->rot_speed = 0.05;
	return (ray);
}

void	init_dir(t_game *game)
{
	if (game->info->w == 1)
	{
		game->ray->dirX = -1.0;
		game->ray->dirY = 0.0;
		game->ray->planeX = 0.0;
		game->ray->planeY = 0.66;
	}
	else if (game->info->e == 1)
	{
		game->ray->dirX = 1.0;
		game->ray->dirY = 0.0;
		game->ray->planeX = 0.0;
		game->ray->planeY = -0.66;
	}
	else if (game->info->s == 1)
	{
		game->ray->dirX = 0.0;
		game->ray->dirY = -1.0;
		game->ray->planeX = 0.66;
		game->ray->planeY = 0.0;
	}
	else if (game->info->n == 1)
	{
		game->ray->dirX = 0.0;
		game->ray->dirY = 1.0;
		game->ray->planeX = -0.66;
		game->ray->planeY = 0.0;
	}
}

void	init_buf(t_game *game)
{
	int	i;

	i = 0;
	game->ray->buf = (int **)malloc(sizeof(int *) * (H + 1));
	while (i < H)
	{
		game->ray->buf[i] = (int *)ft_calloc(sizeof(int), W);
		i++;
	}
	game->ray->buf[i] = NULL;
	game->ray->texture = (int **)malloc(sizeof(int *) * 5);
	i = 0;
	while (i < 5)
	{
		game->ray->texture[i] = (int *)ft_calloc(sizeof(int), (64 * 64));
		i++;
	}
	game->ray->texture[i] = NULL;
}

t_game	*init_game(void)
{
	t_game	*game;
	t_info	*info;
	t_img	*img;
	t_wall	*wall;

	game = (t_game *)safe_malloc(sizeof(t_game));
	info = (t_info *)safe_malloc(sizeof(t_info));
	img = (t_img *)safe_malloc(sizeof(t_img));
	wall = (t_wall *)safe_malloc(sizeof(t_wall));
	ft_memset(game, 0, sizeof(t_game));
	ft_memset(info, 0, sizeof(t_info));
	ft_memset(img, 0, sizeof(t_img));
	ft_memset(wall, 0, sizeof(t_wall));
	game->info = info;
	game->img = img;
	game->ray = init_ray();
	game->wall = wall;
	game->mlx = mlx_init();
	return (game);
}
