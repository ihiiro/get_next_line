/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:00:36 by yel-yaqi          #+#    #+#             */
/*   Updated: 2023/12/11 18:23:47 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ysubstr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	int		size;
	size_t	substr_len;
	int		i;

	if (!s)
		return (0);
	if (ystrlen(s) < start)
		return (ystrdup(""));
	substr_len = ystrlen(s + start);
	if (substr_len < len)
		len = substr_len;
	size = sizeof(char) * (len + 1);
	substr = (char *)malloc(size);
	if (!substr)
		return (0);
	i = 0;
	while (s[start] && i < size - 1)
	{
		substr[i] = s[start];
		start++;
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

int	fill_line(char **line, char *reader, char *remainder)
{
	char	*fr_line;
	char	*new_line_ptr;

	fr_line = *line;
	*line = ystrjoin(*line, reader);
	if (!*line)
		return (free(fr_line), 0);
	free(fr_line);
	new_line_ptr = ystrchr(*line, '\n');
	if (new_line_ptr)
	{
		while (*reader != '\n')
			reader++;
		reader++;
		while (*reader)
			*remainder++ = *reader++;
		*remainder = '\0';
		fr_line = *line;
		*line = ysubstr(*line, 0, (new_line_ptr + 1) - *line);
		if (!*line)
			return (free(fr_line), 0);
		free(fr_line);
	}
	return (1);
}

char	*yget_line(int fd, char *remainder, char *reader, char **line)
{
	ssize_t	rd;

	while (1)
	{
		rd = read(fd, reader, BUFFER_SIZE);
		if (rd == 0)
		{
			if (ystrlen(*line) > 0)
				return (*line);
			else
				return (free(*line), NULL);
		}
		if (rd < 0)
			return (free(*line), NULL);
		reader[rd] = '\0';
		if (!fill_line(line, reader, remainder))
			return (NULL);
		if (!line)
			return (NULL);
		if (ystrchr(*line, '\n'))
			break ;
	}
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	r[BUFFER_SIZE + (size_t)1];
	char		reader[BUFFER_SIZE + (size_t)1];
	char		*line;
	size_t		i;

	if (BUFFER_SIZE == 0 || fd < 0 || read(fd, reader, 0) < 0)
		return (ymemset(r, 0, BUFFER_SIZE), NULL);
	line = NULL;
	i = 0;
	while (!r[i] && i < BUFFER_SIZE)
		i++;
	if (!ystrchr(&r[i], '\n'))
	{
		line = ystrdup(&r[i]);
		ymemset(r, 0, BUFFER_SIZE);
		if (!line)
			return (NULL);
	}
	else if (ystrchr(&r[i], '\n'))
	{
		line = ysubstr(&r[i], 0, (ystrchr(&r[i], '\n') + 1) - &r[i]);
		ymemset(&r[i], 0, (ystrchr(&r[i], '\n') + 1) - &r[i]);
		return (line);
	}
	return (yget_line(fd, r, reader, &line));
}
