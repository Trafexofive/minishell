/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:49:30 by mlamkadm          #+#    #+#             */
/*   Updated: 2022/12/05 06:14:36 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	pos_left;
	size_t	pos_right;
	size_t	len;
	char	*str;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	pos_left = 0;
	pos_right = ft_strlen(s1);
	i = 0;
	while (ft_strchr(set, s1[pos_left]) && i < pos_right)
		pos_left++;
	while (ft_strchr(set, s1[pos_right]) && pos_left < pos_right)
		pos_right--;
	len = (pos_right - pos_left + 1);
	str = ft_substr(s1, pos_left, len);
	if (!str)
		return (NULL);
	while (i < len && str[i])
		str[i++] = s1[pos_left++];
	str[i] = '\0';
	return (str);
}
