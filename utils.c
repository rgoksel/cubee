/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sozbayra <sozbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:08:15 by mgur              #+#    #+#             */
/*   Updated: 2024/01/14 21:48:14 by sozbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup2(const char *s1, int i)
{
	int		j;
	int		len;
	char	*dest;

	j = 0;
	len = ft_strlen(s1);
	dest = malloc((len - 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[j] = s1[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

size_t	ft_toklen2(const char *s)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		if (*s != ' ' && *s != ',')
		{
			++ret;
			while (*s && (*s != ' ' && *s != ','))
				++s;
		}
		else
			++s;
	}
	return (ret);
}

char	**ft_split2(const char *s)
{
	char	**ret;
	size_t	i;
	size_t	len;

	if (!s)
		return (0);
	i = 0;
	ret = malloc(sizeof(char *) * (ft_toklen2(s) + 1));
	if (!ret)
		return (0);
	while (*s)
	{
		if (*s != ' ' && *s != ',')
		{
			len = 0;
			while (*s && (*s != ',' && *s != ' ') && ++len)
				++s;
			ret[i++] = ft_substr(s - len, 0, len);
		}
		else
			++s;
	}
	ret[i] = 0;
	return (ret);
}

int	ft_strcmp(char *str, char *str2 )
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != str2[i])
			return (0);
		i++;
	}
	if (str2[i] != '\0')
		return (0);
	return (1);
}

int	check_elements_same(t_fm *map)
{
	if (ft_strcmp(map->no, map->so) || ft_strcmp(map->no, map->ea) \
	|| ft_strcmp(map->no, map->we))
		return (1);
	else if (ft_strcmp(map->so, map->ea) || ft_strcmp(map->so, map->we) \
	|| ft_strcmp(map->ea, map->we))
		return (1);
	return (0);
}
