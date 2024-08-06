/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:54:43 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/06 14:50:33 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	replace_var_2(char *new, char *newstr, int *i_new, int len)
{
	int	i;

	i = *i_new;
	while (newstr && *newstr)
	{
		new[i] = *newstr;
		newstr++;
		i++;
	}
	new[i] = '\0';
	return (len);
}

int	replace_var_util(char *str, int length, char *new, int *i_new)
{
	int		i;
	char	*newstr;
	char	*string;

	newstr = NULL;
	i = -1;
	string = malloc(sizeof(char) * (length + 1));
	if (!string)
		return (0);
	while (++i < length)
		string[i] = str[i];
	string[i] = 0;
	free(string);
	if (newstr)
		replace_var_2(new, newstr, i_new, length);
	return (length);
}

int	replace_var(t_varcomb vc, int index, char *new, int *i_new)
{
	int		length;

	if (vc.s[index] == '?')
		return (replace_var_2(new, 0, i_new, 1));
	length = envvar_len(vc.s);
	if (!length)
		return (0);
	if (length < 0)
	{
		change_single_env(&vc);
		return (replace_var_2(new, "$", i_new, 0));
	}
	length = replace_var_util(vc.s, length, new, i_new);
	return (length);
}

int	check_envvar(t_varcomb vc, char *new, int *i_new, t_varquote i)
{
	int	t;
	int	variable_len;

	t = i.a;
	while (vc.s[i.a] != '\0' && i.a < i.i)
	{
		if (vc.s[i.a] == '$' && vc.s[i.a + 1])
		{
			variable_len = replace_var(vc, i.a + 1, new, i_new);
			change_single_env(&vc);
			*i_new = (int)ft_strlen(new);
			i.a = i.a + variable_len + 1;
		}
		else if ((vc.s[i.a] == '\'' && i.qt == 1 && !s_ck(vc.s, t, i.i, '\''))
			|| (vc.s[i.a] == '\"' && i.qt == 2 && !s_ck(vc.s, t, i.i, '\"')))
			i.a++;
		else
		{
			new[*i_new] = vc.s[i.a];
			i.a++;
			*i_new = *i_new + 1;
		}
	}
	check_envvar_util(new, i_new);
	return (i.a);
}

/*
Replaces quotes and takes only the input string
Returns whether quote exists or no
*/
int	replace_quote(t_varcomb vc, char *new, int *i, int *i_new)
{
	int	quote;
	int	qt;
	int	a;

	a = *i;
	quote = 0;
	qt = check_quote(i, vc.s);
	if (qt == 1 || qt == 2)
		quote = 1;
	while (a < *i)
	{
		if (quote == 1 && vc.s[a] == '\'')
		{
			if (check_ds(vc.s, a, *i) && !sq_dollar(vc.s, '\''))
				a = check_envvar(vc, new, i_new, (t_varquote){a, *i, qt});
		}
		else
			a = replace_double(vc, new, i_new, (t_varquote){a, *i, qt});
		a++;
	}
	new[(*i_new) + 1] = '\0';
	*i_new = ft_strlen(new);
	return (quote);
}
