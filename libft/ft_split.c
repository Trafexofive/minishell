/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 06:02:23 by mlamkadm          #+#    #+#             */
/*   Updated: 2022/12/12 16:13:00 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static int	ft_word_count(const char *s, char delim)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (*s)
	{
		if (*s != delim && flag == 0)
		{
			i++;
			flag = 1;
		}
		else if (*s == delim)
			flag = 0;
		s++;
	}
	return (i);
}

static char	*word_alloc(const char *s, int start, int finish)
{
	int		i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	str = (char *)malloc (sizeof(char) * (finish - start + 1));
	if (!str)
		return (NULL);
	while (start < finish)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

char	**ft_root_split(char **two_d_array, const char *s, char c, size_t s_len)
{
	size_t	i;
	size_t	j;
	int		last_occurence;

	i = 0;
	j = 0;
	last_occurence = -1;
	while (i <= s_len)
	{
		if (s[i] != c && last_occurence < 0)
			last_occurence = i;
		else if ((s[i] == c || i == s_len) && last_occurence >= 0)
		{
			two_d_array[j++] = word_alloc(s, last_occurence, i);
			if (!two_d_array[j - 1])
			{
				ft_free(two_d_array);
				return (NULL);
			}
			last_occurence = -1;
		}
		i++;
	}
	two_d_array[j] = 0;
	return (two_d_array);
}

char	**ft_split(const char *s, char c)
{
	char	**two_d_array;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	two_d_array = (char **) malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	if (!two_d_array)
		return (NULL);
	return (ft_root_split(two_d_array, s, c, s_len));
}
