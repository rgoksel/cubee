/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgur <mgur@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:19:18 by mgur              #+#    #+#             */
/*   Updated: 2022/11/10 15:19:18 by mgur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr3(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if ((size_t)start > ft_strlen3(s))
		return (ft_strdup3(""));
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strchr3(const char *s, int c)
{
	size_t	i;
	size_t	len;

	len = ft_strlen3(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (0);
}

char	*ft_strdup3(const char *s1)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = ft_strlen3(s1);
	dest = malloc(len + 1 * sizeof(char));
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin3(char const *s1, char const *s2)
{
	size_t		i;
	char		*dizi;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	dizi = malloc(sizeof(char) * (ft_strlen3(s1) + ft_strlen3(s2) + 1));
	if (dizi == NULL)
		return (NULL);
	while (*s1)
		dizi[i++] = *s1++;
	while (*s2)
		dizi[i++] = *s2++;
	dizi[i] = '\0';
	return (dizi);
}

size_t	ft_strlen3(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
