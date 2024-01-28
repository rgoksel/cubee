/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 01:14:38 by mgur              #+#    #+#             */
/*   Updated: 2024/01/25 14:56:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_elements_valid(char *str)
{
	if (ft_strncmp(str, "NO", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "SO", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "WE", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "EA", 3) == 0)
		return (1);
	else
		return (0);
}

int	check_map(char *str, t_cub3d **cub3d)
{
	int		line;
	int		fd;
	char	*check;

	line = 0;
	fd = open(str, O_RDONLY);
	check = get_next_line(fd); //line line verilen map dosyasını aldı ve pointerda ilk lineı tutuyor şuanda 
	while (check != NULL && !(*cub3d)->map.check) // başta mapcheck 0 so ilk runda bu kısımı atlicak
	{
		//ama eğer atlamadığı döngüde ....
		if (!is_space(check) || (!(check[0] == '\0') && check_map2(check, cub3d) == 1))
		{
			let_free((*cub3d));
			ft_error("error");
			exit(1);
		}
		free(check);
		check = get_next_line(fd);
		line++;
	}
	check_map_clone(str, cub3d, line);
	free(check);
	close(fd);
	return (0);
}

void	if_max(t_fm *map, char *check)
{
	if (map->max_line_c < (int)ft_strlen(check))
		map->max_line_c = ft_strlen(check);
	map->lines++;
}

void	check_map_clone(char *str, t_cub3d **cub3d, int line)
{
	if (!(*cub3d)->map.ea || !(*cub3d)->map.no || !(*cub3d)->map.so
		|| !(*cub3d)->map.we || (*cub3d)->map.c == -1
		|| (*cub3d)->map.f == -1 || check_elements_same(&(*cub3d)->map))
	{
		let_free((*cub3d));
		printf("Missing elements\n");
		exit(1);
	}
	if (count_of_map_line(line, str, &(*cub3d)->map))
	{
		let_free((*cub3d));
		printf("Map error\n");
		exit(1);
	}
	take_care_the_map(&(*cub3d)->map, str, line);
	if ((*cub3d)->map.direct == 'G' || check_map_valid(&(*cub3d)->map, &(*cub3d)->player))
	{
		let_free((*cub3d));
		printf("Map is not surrounded by walls\n");
		exit(1);
	}
}
