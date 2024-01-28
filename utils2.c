/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgur <mgur@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 09:57:48 by mgur              #+#    #+#             */
/*   Updated: 2024/01/15 11:54:40 by mgur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_it(t_fm *map)
{
	int	i;

	i = 0;
	while (i < map->lines + 1)
	{
		printf("%s\n", map->map[i]);
		i++;
	}
}

int	check_dot(char *str)
{
	int	fd;
	int	len;

	len = ft_strlen(str);
	if (str[0] == '.' && str[1] == '/' && str[--len] == 'm' \
	&& str[--len] == 'p' && str[--len] == 'x' && str[--len] == '.')
	{
		fd = open(str, O_RDONLY);
		if (fd <= 0)
		{
			close(fd);
			return (1);
		}
		else
		{
			close(fd);
			return (0);
		}
	}
	else
		return (1);
}

int	is_same(char *str, char *str2)
{
	if ((str[0] == str2[0]) && (str[1] == str2[1]) && (str[2] == '\0'))
		return (1);
	return (0);
}

int	ft_atoiup(char *str)
{
	long	i;
	long	result;

	i = 0;
	result = 0;
	if(!is_space(str))
		return(-1);
	while (str[i] && (str[i] == 32))
		i++;
	while (ft_isdigit(str[i]))
	{
		result = (str[i] - 48) + (result * 10);
		if (result > 256)
			return (-1);
		i++;
	}
	while (str[i] && (str[i] == 32))
		i++;
	if (str[i] != '\0')
		return (-1);
	return (result);
}

int	mapline_ut(int fd, char *str, int line)
{
	char	*check;
	int		i;

	fd = open(str, O_RDONLY);
	check = get_next_line(fd);
	while (check)
	{
		free(check);
		check = get_next_line(fd);
	}
	free(check);
	close(fd);
	fd = open(str, O_RDONLY);
	i = 0;
	while (i < line)
	{
		check = get_next_line(fd);
		free(check);
		i++;
	}
	return (fd);
}
