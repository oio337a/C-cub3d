/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:17:25 by yongmipa          #+#    #+#             */
/*   Updated: 2023/05/15 21:01:21 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# include "queue.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>



typedef struct s_map // 맵에 대한 정보 담긴 구조체
{
	char	**map;
	int		**f;
	int		**c;
}	t_map;

typedef struct s_img //이미지, 해상도 담긴 구조체
{
	void	*north;
	void	*south;
	void	*west;
	void	*east;
}	t_img;

typedef struct s_game
{
	void	*mlx;
	void	*window;
	int		*info_flag[6];
	int		w;
	int		a;
	int		s;
	int		d;
	t_img	*img;
	t_map	*map;
}	t_game;

/* utils.c */
void	ft_free(char **str);
int		ft_size(char **str);
int		ft_isspace(char c);
void	ft_err(char *str);


/*validation*/
int	ft_str_col(char **map);
int	is_whitespace(char *str);
int	whitespace(char c);
int	start_end_wall(char *map);
int	check_wall(char *map, int len);
int	all_around_wall(char **map); // 이차원이라 생각할게여
int	context_check(char context, t_game *dir);
int	mid_context_check(char **map, t_game *dir); //WASD, 1, 0만 있어야댐
void	append_space_index(char **map, t_queue *q);
int	bfs_test(char **map);
//gnl
char	*get_next_line(int fd);


#endif