/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 02:04:59 by mlamkadm          #+#    #+#             */
/*   Updated: 2022/12/12 16:14:33 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_whitespace(const char c)
{
	if (c == '\n' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (0);
	else
		return (1);
}

int	ft_atoi(const char *str)
{
	unsigned int	int_value;
	int				i;
	int				sign;

	int_value = 0;
	i = 0;
	sign = 1;
	while (ft_whitespace(str[i]) == 0)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = sign * -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		int_value = (int_value * 10) + (str[i] - '0');
		i++;
	}
	return (int_value * sign);
}
