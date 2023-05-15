/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhwpark <suhwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:42:48 by yongmipa          #+#    #+#             */
/*   Updated: 2023/05/15 20:52:26 by suhwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define MIN_INT -2147483648

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
		if ((res & MIN_INT) != 0)
			return (-1);
	}
	if (!i && !str[i])
		return (-1);
	if (!('0' <= str[i] && str[i] <= '9') && str[i])
		return (-1);
	return (res);
}
