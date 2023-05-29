/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:08:44 by yongmipa          #+#    #+#             */
/*   Updated: 2023/05/29 17:03:20 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	leak(void)
{
	system("leaks cub3D");
}

int	main(int ac, char *av[])
{
	t_game	*game;
	int		fd;

	atexit(leak);
	if (ac != 2)
		ft_err("invalid argument count", 0);
	if (!check_extension(av[1], ".cub"))
		ft_err("invalid file argument extention", 0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		ft_err("Failed to open file", 0);
	game = init_game();
	if (!validate_all(read_file(fd, game), game))
		ft_err("map error!", game);
	close(fd);
	game->window = mlx_new_window(game->mlx, W, H, "cub3D");
	game->info->map[(int)game->info->p_pos[0]][(int)game->info->p_pos[1]] = '0';
	raycasting(game);
	return (0);
}
