/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:42:36 by mlamkadm          #+#    #+#             */
/*   Updated: 2022/12/04 04:35:31 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;
	size_t	final_len;
	char	*src_ptr;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	src_ptr = (char *)src;
	if (dstsize > dst_len)
		final_len = dst_len + src_len;
	else
		final_len = src_len + dstsize;
	while (src_ptr[i] && dst_len + 1 < dstsize)
	{
		dst[dst_len] = src_ptr[i];
		i++;
		dst_len++;
	}
	dst[dst_len] = '\0';
	return (final_len);
}
