/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:52:30 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/06 17:54:36 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Add freeing functions!

/*
From the transition of the table (each line) takes
1. state
2. token type or event (common convention)
3. action to take
4. next state to go
5. number of reduced tokens
*/

t_table	*ft_add_table_line(char **arg_line)
{
	t_table	*table_line;

	if (!arg_line)
		return (NULL);
	table_line = (t_table *)malloc(sizeof(*table_line));
	if (!table_line)
		return (NULL);
	table_line->state = ft_atoi(arg_line[0]);
	table_line->token_type = ft_atoi(arg_line[1]);
	table_line->action = ft_atoi(arg_line[2]);
	table_line->next_state = ft_atoi(arg_line[3]);
	table_line->nb_reduce = ft_atoi(arg_line[4]);
	return (table_line);
}

/*
Takes all the transitions of the table (lines)
*/

void	free_line_args(char *line, char **args)
{
	char	**begin;

	if (line)
		free(line);
	if (args)
	{
		begin = args;
		while (*args)
		{
			free(*args);
			++args;
		}
		free(begin);
	}
}

int	ft_create_table_state(int fd, t_table **table)
{
	char	*line;
	char	**arg_line;
	int		i;
	int		a;

	i = 0;
	line = NULL;
	a = ft_get_next_line(fd, &line);
	while (a >= 0)
	{
		// printf("line = %s", line);
		// if (line == NULL)
		// {
		// 	fprintf(stderr, "Error reading line %d: line is NULL.\n", i);
		// 	return (-1);
		// }
		arg_line = ft_split(line, 9);
		// int j = 0;
		// while (arg_line[j])
		// {
		// 	printf("%d = %s ", j, arg_line[j]);
		// 	j++;
		// }
		if (!arg_line)
		{
			fprintf(stderr, "Error splitting line %d: split failed.\n", i);
			free(line);
			return (-1);
		}
		table[i] = ft_add_table_line(arg_line);
		if (!table[i])
		{
			fprintf(stderr, "Error adding table line %d: add failed.\n", i);
			free_line_args(line, arg_line);
			return (-1);
		}
		i++;
		// printf ("a = %d\n", a);
		free_line_args(line, arg_line);
		line = NULL;
		if (a == 0)
			break ;
		a = ft_get_next_line(fd, &line);
		if (a == 0)
			break ;
		// printf("a1 = %d\n", a);
	}
	if (a == -1)
	{
		fprintf(stderr, "Error reading from file: ft_get_next_line failed.\n");
		return(-1);
	}
	return (0);
}

void	ms_free_table(t_table **trans)
{
	t_table	**begin;

	begin = NULL;
	if (trans)
	{
		begin = trans;
		while (*trans)
		{
			free(*trans);
			++trans;
		}
		free(begin);
	}
}

/*
Takes all the data from the AUTOMATON
*/

t_table	**ft_init_parsing_table(char *path)
{
	t_table	**table;
	int		fd;

	table = (t_table **)malloc(sizeof(*table) * (LINES + 1));
	if (!table)
		return (NULL);
	table[0] = NULL;
	table[LINES] = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ms_free_table(table);
		return (NULL);
	}
	if (ft_create_table_state(fd, table) == -1)
	{
		fprintf(stderr, "Failed to create table state from file: %s\n", path);
		ms_free_table(table);
		close (fd);
		return (NULL);
	}
	close(fd);
	//int i = 0;
	// while (table[i] != NULL)
	// {
	// 	printf("i = %d, -> %d, %d, %d, %d, %d\n", i, table[i]->state, table[i]->token_type, table[i]->action, table[i]->next_state, table[i]->nb_reduce);
	// 	i++;
	// }
	return (table);
}
