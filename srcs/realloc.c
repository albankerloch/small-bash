/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:13:12 by aduchemi          #+#    #+#             */
/*   Updated: 2020/11/06 22:13:14 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_realloc_fix_error(char **arg, int *i)
{
	(*i)++;
	if (fix.error >= 100)
	{
		if (!(*arg = ft_realloc_concat(*arg, fix.error / 100 + 48)))
			return (0);
	}
	if (fix.error >= 10)
	{
		if (!(*arg = ft_realloc_concat(*arg, fix.error % 100 / 10 + 48)))
			return (0);
	}
	if (!(*arg = ft_realloc_concat(*arg, fix.error % 10 + 48)))
		return (0);
	return (1);
}

int		ft_realloc_var(char **arg, char *line, int *i)
{
	int		j;
	int		k;

	j = 0;
	while (line[*i + j] && (ft_isalnum(line[*i + j]) || line[*i + j] == '_'))
		j++;
	k = 0;
	while (fix.env && fix.env[k])
	{
		if (ft_strncmp(fix.env[k], &line[*i], j) == 0 && fix.env[k][j] == '=')
		{
			*i = *i + j - 1;
			j++;
			if (!(*arg = ft_strjoin_free(*arg, &(fix.env[k][j]))))
				return (0);
			return (1);
		}
		k++;
	}
	*i = *i + j - 1;
	return (2);
}

char	*ft_realloc_concat(char *line, char c)
{
	char	*new;

	if (!(new = malloc(sizeof(*new) * (ft_strlen(line) + 2))))
		return (NULL);
	if (ft_strlen(line) > 0)
		ft_memcpy(new, line, ft_strlen(line));
	new[ft_strlen(line)] = c;
	new[ft_strlen(line) + 1] = '\0';
	free(line);
	return (new);
}

char	**ft_realloc_arg(char **arg)
{
	char	**new;
	int		i;

	i = 0;
	while (arg[i])
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 2))))
		return (NULL);
	i = 0;
	while (arg[i])
	{
		if (!(new[i] = ft_strdup(arg[i])))
			return (ft_free_tab(new, i));
		i++;
	}
	if (!(new[i] = malloc(1)))
		return (ft_free_tab(new, i));
	new[i][0] = '\0';
	new[i + 1] = NULL;
	ft_free_tab(arg, i);
	return (new);
}