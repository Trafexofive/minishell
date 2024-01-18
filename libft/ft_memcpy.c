/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:16:32 by mlamkadm          #+#    #+#             */
/*   Updated: 2022/12/11 18:54:56 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int		i;
	char	*dstx;
	char	*srcx;

	if (!dst && !src)
		return (NULL);
	if (!n)
		return (dst);
	i = 0;
	dstx = dst;
	srcx = (char *) src;
	while (n > 0)
	{
		dstx[i] = srcx[i];
		i++;
		n--;
	}
	return (dst);
}
