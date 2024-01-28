/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgur <mgur@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:19:29 by mgur              #+#    #+#             */
/*   Updated: 2022/11/10 15:19:29 by mgur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*last(char **s, char **line)
{
	int		len;
	char	*str;

	len = 0;
	while ((*s)[len] != '\n' && (*s)[len] != '\0')
		len++;
	if ((*s)[len] == '\n')
	{
		*line = ft_substr3(*s, 0, len);
		str = ft_strdup3(&(*s)[len + 1]);
		free(*s);
		*s = str;
		if ((*s)[0] == 0)
		{
			free(*s);
			*s = 0;
		}
	}
	else
	{
		*line = ft_strdup3(*s);
		free(*s);
		*s = 0;
	}
	return (*line);
}

char	*check(char **s, char **line, int count)
{
	if (count <= 0 && *s == NULL)
		return (0);
	return (last(s, line));
}

char	*get_next_line(int fd)
{
	static char	*s;
	char		*line;
	char		*tmp;
	char		buffer[BUFFER_SIZE + 1];
	int			count;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	count = read(fd, buffer, BUFFER_SIZE);
	while (count > 0)
	{
		buffer[count] = 0;
		if (s == NULL)
			s = ft_strdup3(buffer);
		else
		{
			tmp = ft_strjoin3(s, buffer);
			free(s);
			s = tmp;
		}
		if (ft_strchr3(s, '\n'))
			break ;
		count = read(fd, buffer, BUFFER_SIZE);
	}
	return (check(&s, &line, count));
}
