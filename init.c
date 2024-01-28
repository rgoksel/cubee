/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgur <mgur@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:13:36 by mgur              #+#    #+#             */
/*   Updated: 2024/01/13 16:13:36 by mgur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_fc(char c, char **str, t_fm *map)
{
	int	r;
	int	g;
	int	b;

	if (str[3] || !str[2] || !str[0] || !str[1])
	{
		return (1);
	}
	r = ft_atoiup(str[0]);
	g = ft_atoiup(str[1]);
	b = ft_atoiup(str[2]);
	if (r < 0 || r > 256 || g < 0 || g > 256 || b < 0 || b > 256)
		return (1);
	if (c == 'F')
		map->f = (r << 16) + (g << 8) + b;
	else
		map->c = (r << 16) + (g << 8) + b;
	return (0);
}

int	process_element(char **lol, t_cub3d **cub3d, char *element, char **mp)
{
	if (is_same(lol[0], element) && !(*cub3d)->map.check)
	{
		if ((*mp) != NULL || check_dot(lol[1]))
			return (1);
		else
			(*mp) = strdup(lol[1]);
	}
	return (0);
}

int	check_elements(char **lol, t_cub3d **cub3d)
{
	if (process_element(lol, cub3d, "NO", &(*cub3d)->map.no) || \
		process_element(lol, cub3d, "SO", &(*cub3d)->map.so) || \
		process_element(lol, cub3d, "WE", &(*cub3d)->map.we) || \
		process_element(lol, cub3d, "EA", &(*cub3d)->map.ea))
		return (1);
	return (0);
}

void	check_map2_ut(char **lol, t_cub3d **cub3d, char *str)
{
	char	*tmp;
	char	c;

	c = lol[0][0];
	tmp = ft_strdup2(str, for_f(str));
	lol = ft_split(tmp, ',');
	free(tmp);
	if (str[ft_strlen(str) - 1] != ',')
	{
		if ((((c == 'F' && (*cub3d)->map.f == -1)) || (c == 'C'
		&& (*cub3d)->map.c == -1)) && check_fc(c, lol, &(*cub3d)->map))
		{
			free_split(lol);
			ft_error("Invalid FC format");
		}
	}
	else
	{
		free_split(lol);
		ft_error("Invalid FC format");
	}
	free_split(lol);
}

int	check_map2(char *str, t_cub3d **cub3d)
{
	char	**lol;

	lol = ft_split(str, ' ');
	if (check_for_m2(lol))
	{
		free_split(lol);
		ft_error("error");
	}
	if (check_elements_valid(lol[0]))
	{
		if (!lol[1] || check_elements(lol, cub3d))
		{
			free_split(lol);
			ft_error("error");
		}
	}
	else if ((lol[0][0] == 'F' || lol[0][0] == 'C') \
	&& lol[0][1] == '\0' && !(*cub3d)->map.check)
		check_map2_ut(lol, cub3d, str);
	else if (lol[0][0] == '1')
		(*cub3d)->map.check = 1;
	else
	{
		free_split(lol);
		ft_error("error");
	}
	free_split(lol);
	return (0);
}
