/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   takeMap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgur <mgur@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:00:38 by mgur              #+#    #+#             */
/*   Updated: 2024/01/15 02:45:21 by mgur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	take_map_ut(t_fm *map, int i)
{
	int	j;

	j = 0;
	map->map[i] = malloc(map->max_line_c + 2);
	while (j < map->max_line_c + 2)
		map->map[i][j++] = '-';
	map->map[i][j] = '\0';
}

void	take_map_ut2(t_fm *map, char *check, int i, int j)
{
	while (j < map->max_line_c + 1)
	{
		map->map[i][0] = '-';
		if (check[0] == '\0')
			map->map[i][j] = '-';
		else if ((check[j] && (check[j] == ' ' || check[j] == '\0' ))
			|| j > (int)ft_strlen(check) - 1)
			map->map[i][j + 1] = '-';
		else
			map->map[i][j + 1] = check[j];
		j++;
		map->map[i][j + 1] = '\0';
	}
}

void	take_care_the_map(t_fm *map, char *str, int line)
{
	int		i;
	int		j;
	char	*check;
	int		fd;

	i = 1;
	fd = mapline_ut(1, str, line - 1);
	map->map = (char **)malloc((map->lines + 2) * sizeof(char *));
	take_map_ut(map, 0);
	check = get_next_line(fd);
	while (check)
	{
		map->map[i] = malloc(map->max_line_c + 2);
		j = 0;
		take_map_ut2(map, check, i, j);
		i++;
		free(check);
		check = get_next_line(fd);
	}
	free(check);
	take_map_ut(map, i);
}
