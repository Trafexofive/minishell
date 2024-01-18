/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:57:15 by mlamkadm          #+#    #+#             */
/*   Updated: 2022/12/10 11:44:40 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (needle_len == 0 || h == needle)
		return ((char *)h);
	while (h[i] != '\0' && i < len)
	{
		j = 0;
		while (h[i + j] != '\0' && needle[j] != '\0'
			&& h[i + j] == needle[j] && i + j < len)
			j++;
		if (j == needle_len)
			return ((char *)h + i);
		i++;
	}
	return (NULL);
}
