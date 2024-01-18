/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:08:58 by mlamkadm          #+#    #+#             */
/*   Updated: 2022/12/09 09:04:03 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_len(int num)
{
	int	num_len;

	num_len = 1;
	if (num <= 0)
		num_len = 2;
	while (num != 0)
	{
		num = num / 10;
		num_len++;
	}
	return (num_len);
}

static char	*ft_num_alloc(int num_len)
{
	char	*num_str;

	num_str = (char *)malloc((sizeof(char) * num_len));
	if (!num_str)
		return (NULL);
	return (num_str);
}

static int	ft_is_negative(int num)
{
	int	is_negative;

	is_negative = 0;
	if (num < 0)
		is_negative = 1;
	return (is_negative);
}

char	*ft_itoa(int num)
{
	int			num_len;
	char		*num_str;
	long int	n;

	n = num;
	num_len = ft_num_len(n);
	num_str = ft_num_alloc(num_len);
	if (!num_str)
		return (NULL);
	if (ft_is_negative(num) == 1)
		n = -n;
	num_len--;
	num_str[num_len] = '\0';
	while (num_len-- > 0)
	{
		num_str[num_len] = (n % 10) + '0';
		n = n / 10;
	}
	if (ft_is_negative(num) == 1)
		num_str[0] = '-';
	return (num_str);
}
