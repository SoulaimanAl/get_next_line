/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soulaimane <soulaimane@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:23:15 by soulaimane        #+#    #+#             */
/*   Updated: 2024/11/27 12:02:40 by soulaimane       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*help_get_next(char **res, char *buf, int fd)
{
	char	*d;
	int		n;
	int		i;

	n = 1;
	while (n > 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n <= 0)
			break ;
		buf[n] = '\0';
		d = *res;
		*res = ft_strjoin(*res, buf);
		free(d);
		if (!*res)
			return (free(buf), NULL);
		i = 0;
		while ((*res)[i] && (*res)[i] != '\n')
			i++;
		if ((*res)[i] == '\n')
			return (free(buf), take_line_from_res(res, i, 1));
	}
	if (n == -1 || (n == 0 && (!*res || **res == '\0')))
		return (free(buf), free(*res), *res = NULL, NULL);
	return (free(buf), take_line_from_res(res, ft_strlen(*res), 0));
}

char	*get_next_line(int fd)
{
	static char	*res[1024];
	char		*buf;
	char		*line;
	size_t		i;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	buf = malloc((BUFFER_SIZE * sizeof(char)) + 1);
	if (buf == NULL)
		return (free(res[fd]), res[fd] = NULL, NULL);
	if (res[fd])
	{
		i = 0;
		while (res[fd][i] && res[fd][i] != '\n')
			i++;
		if (res[fd][i] == '\n')
		{
			line = take_line_from_res(&res[fd], i, 1);
			return (free(buf), line);
		}
	}
	return (help_get_next(&res[fd], buf, fd));
}
