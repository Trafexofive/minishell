/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:28:38 by mlamkadm          #+#    #+#             */
/*   Updated: 2022/12/11 23:48:42 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	if (s1 == s2)
		return (0);
	while (n-- > 0)
	{
		if (*ss1 != *ss2)
			return (*(unsigned char *)ss1 - *(unsigned char *)ss2);
		ss1++;
		ss2++;
	}
	return (0);
}

// int main(void)
// {
// 	int s1 = 35355;
// 	int s2 = 888;

// 	printf("%d", ft_memcmp(&s1, &s2, 5));
// }

// // 00000000 00000000 10001010 00011011
// // 00000000 00000000 00000011 01111000