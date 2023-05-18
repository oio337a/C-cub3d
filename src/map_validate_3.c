/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:36:29 by sohyupar          #+#    #+#             */
/*   Updated: 2023/05/18 21:16:36 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

static int	word_len2(const char *s, char c)
{
	int	i;
	int	wordlen;

	i = 0;
	wordlen = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		wordlen++;
	}
	return (wordlen);
}

static char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*word;

	i = 0;
	word = (char *)malloc(sizeof(char) * (n + 1));
	if (!word)
		return (0);
	while (i < n)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_free2(char **list, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(list[i]);
		i++;
	}
	free(list);
	return (0);
}

char	**ft_split2(char const *s, char c)
{
	int		i;
	int		wordlen;
	int		count;
	char	**word;
	int		len;

	len = 0;
	i = 0;
	if (!*s)
		return (NULL);
	count = word_count(s, c) + 1;
	while (*s && *s == c)
		s++;
	word = (char **)malloc(sizeof(char *) * (count + 1));
	if (!word)
		return (0);
	while (i < count)
	{
		if (*s && *s == c)
			s++;
		wordlen = word_len2(s, c);
		if (wordlen == 0)
		{
			len = ft_strlen(word[i - 1]);
			word[i] = (char *)malloc(sizeof(char) * len + 1);
			ft_memset(word[i], ' ', len);
			word[i][len] = '\0';
		}
		else
			word[i] = ft_strndup(s, wordlen);
		if (!word[i])
			return (ft_free2(word, i));
		s += wordlen;
		i++;
	}
	word[count] = 0;
	return (word);
}
