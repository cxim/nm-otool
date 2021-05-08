/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarwhal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 16:58:18 by mnarwhal          #+#    #+#             */
/*   Updated: 2020/08/22 17:00:13 by mnarwhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_words(char *line)
{
	int		count;

	count = 0;
	while (*line)
	{
		while (*line && (*line == ' ' || *line == '\n' || *line == '\t'))
			line++;
		if (*line && *line != ' ' && *line != '\n' && *line != '\t')
		{
			count++;
			while (*line && *line != ' ' && *line != '\n' && *line != '\t')
				line++;
		}
	}
	return (count);
}

char	*get_words(const char *line)
{
	char	*word;
	int		i;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
	{
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**my_split(char *line)
{
	int		words;
	int		i;
	char	**arr;

	words = count_words(line);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	i = 0;
	while (*line)
	{
		while (*line && (*line == ' ' || *line == '\n' || *line == '\t'))
			line++;
		if (*line && *line != ' ' && *line != '\n' && *line != '\t')
		{
			arr[i] = get_words(line);
			i++;
			while (*line && *line != ' ' && *line != '\n' && *line != '\t')
				line++;
		}
	}
	arr[i] = NULL;
	return (arr);
}
