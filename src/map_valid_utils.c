/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:21:52 by sohyupar          #+#    #+#             */
/*   Updated: 2023/05/25 21:26:44 by suhwpark         ###   ########.fr       */
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

char	**freeall(char **str, int cnt)
{
	int	i;

	i = 0;
	while (i < cnt)
		free(str[i++]);
	free(str);
	return (NULL);
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
