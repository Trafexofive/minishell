/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:31:59 by mlamkadm          #+#    #+#             */
/*   Updated: 2022/12/11 08:57:15 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dupped_str;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	dupped_str = (char *)malloc (sizeof(char) * (len + 1));
	if (!dupped_str)
		return (NULL);
	while (s1[i])
	{
		dupped_str[i] = s1[i];
		i++;
	}
	dupped_str[i] = '\0';
	return (dupped_str);
}
