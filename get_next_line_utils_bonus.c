/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:31:13 by yel-yaqi          #+#    #+#             */
/*   Updated: 2023/12/11 17:23:45 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ystrdup(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = 0;
	while (*(s1 + len))
		len++;
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		*(dup + i) = *(s1 + i);
		i++;
	}
	*(dup + i) = '\0';
	return (dup);
}

size_t	ystrlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

char	*ystrjoin(char const *s1, char const *s2)
{
	char	*joint;
	int		i;

	if (s1 == NULL && s2)
		return (ystrdup(s2));
	if (s2 == NULL && s1)
		return (ystrdup(s1));
	if (!s1 && !s2)
		return (NULL);
	i = -1;
	joint = (char *)malloc(sizeof(char) * (ystrlen(s1) + ystrlen(s2) + 1));
	if (!joint)
		return (NULL);
	while (s1[++i])
		joint[i] = s1[i];
	while (*s2)
		joint[i++] = *s2++;
	joint[i] = '\0';
	return (joint);
}

char	*ystrchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ymemset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(char *)(b + i) = (unsigned char)c;
		i++;
	}
	return (b);
}
