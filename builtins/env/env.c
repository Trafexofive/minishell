/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 00:23:07 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/06 17:38:25 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	env_b(t_list *env_var, t_commands *args)
{
	if (!env_var)
	{
		g_exit_status = 0;
		return (0);
	}
	ft_lstprint_str(env_var, args->out);
	g_exit_status = 0;
	return (0);
}
