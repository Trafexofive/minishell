/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:27:33 by mlamkadm          #+#    #+#             */
/*   Updated: 2022/12/12 16:14:12 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dstx;
	char	*srcx;

	dstx = (char *) dst ;
	srcx = (char *) src ;
	i = n;
	if (!dst && !src)
		return (NULL);
	if (!n)
		return (dst);
	while (n > 0 && i-- >= 0 && dstx > srcx)
	{
		dstx[i] = srcx[i];
		n--;
	}
	i = 0;
	while (n-- > 0)
	{
		dstx[i] = srcx[i];
		i++;
	}
	return (dst);
}
