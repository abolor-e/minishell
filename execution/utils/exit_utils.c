/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:07:12 by marechaloli       #+#    #+#             */
/*   Updated: 2024/08/04 02:35:36 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exit_status(int status, t_envb *env)
{
	if (status == 28)
	{
		env->exstatus = 1;
		return (1);
	}
	if (WIFSIGNALED(status))
	{
		env->exstatus = 128 + WTERMSIG(status);
		return (128 + WTERMSIG(status));
	}
	env->exstatus = WEXITSTATUS(status);
	return (WEXITSTATUS(status));
}
