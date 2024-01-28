/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forMap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgur <mgur@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:07:21 by mgur              #+#    #+#             */
/*   Updated: 2024/01/15 11:54:26 by mgur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_space(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		i++;
		if (str[i] != ' ' || str[i] != 0)
		{
			return (1);
		}
	}
	return (0);
}

int	check_valid_chars(char *str, t_fm *map)
{
	if (!is_space(str))
		return (0);
	while (*str != '\0')
	{
		if (*str != '0' && *str != '1' && *str != ' ')
		{
			if (*str == 'N' && map->direct == 'G')
				map->direct = 'N';
			else if (*str == 'W' && map->direct == 'G')
				map->direct = 'W';
			else if (*str == 'E' && map->direct == 'G')
				map->direct = 'E';
			else if (*str == 'S' && map->direct == 'G')
				map->direct = 'S';
			else
				return (0);
		}
		str++;
	}
	return (1);
}

int	count_of_map_line(int line, char *str, t_fm *map)
{
	char	*check;
	int		fd;

	fd = mapline_ut(1, str, line - 1);
	map->lines = 1;
	check = get_next_line(fd);
	while (check)
	{
		if (check_valid_chars(check, map))
			if_max(map, check);
		else
		{
			printf("empty line\n");
			free(check);
			close(fd);
			return (1);
		}
		free(check);
		check = get_next_line(fd);
	}
	free(check);
	close(fd);
	return (0);
}

int	check_map_valid2(t_fm *map, t_fp *player, int i, int j)
{
	if (map->map[i][j + 1] == '-' || map->map[i][j - 1] == '-'
		|| map->map[i + 1][j] == '-' || map->map[i - 1][j] == '-')
		return (1);
	player->pos_x = i + 0.5;
	player->pos_y = j + 0.5;
	return (0);
}

int	check_map_valid(t_fm *map, t_fp *player)
{
	int	i;
	int	j;

	i = 1;
	while (i < map->lines + 1)
	{
		j = 1;
		while (j < map->max_line_c + 1)
		{
			if (map->map[i][j] == '0')
			{
				if (map->map[i][j + 1] == '-' || map->map[i][j - 1] == '-'
					|| map->map[i + 1][j] == '-' || map->map[i - 1][j] == '-')
					return (1);
			}
			else if (map->map[i][j] == map->direct)
				if(check_map_valid2(map, player, i, j))
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}
