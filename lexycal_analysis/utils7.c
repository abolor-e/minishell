/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:14:14 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/20 14:14:15 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sep_util(char *line, int a, t_sdQuote *sdq)
{
	if (line[a] == '\'')
		sdq->single_q++;
	if (line[a] == '\"')
		sdq->double_q++;
}

void	initial(char *new)
{
	int	i;

	i = -1;
	while (++i < 1000)
		new[i] = '\0';
}

void	change_single_env(t_varcomb *vc)
{
	char	*tmp;

	tmp = NULL;
	if (vc->s[0] == '\'' && vc->s[ft_strlen(vc->s) - 1] == '\'')
	{
		tmp = vc->s + 2;
		vc->s = ft_strjoin("'$~", tmp);
	}
}

int	envvar_len(char *str)
{
	int	i;

	i = 0;
	if (!(*str))
		return (0);
	if (ft_isdigit(str[0]))
		return (1);
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
			break ;
	}
	if (i == 0)
		return (-1);
	return (i);
}

void	check_envvar_util(char *new, int *i_new)
{
	new[(*i_new) + 1] = '\0';
	*i_new = ft_strlen(new);
}
