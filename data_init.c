/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:06:06 by mgur              #+#    #+#             */
/*   Updated: 2024/01/26 11:57:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//tşlar için başlangıç değeri atadık
void	keys_init(t_cub3d *cub3d)
{
	cub3d->keys.w = 0;
	cub3d->keys.a = 0;
	cub3d->keys.s = 0;
	cub3d->keys.d = 0;
	cub3d->keys.left = 0;
	cub3d->keys.right = 0;
	cub3d->map.width = 1920;
	cub3d->map.height = 1080;
}

void	player_init2(t_cub3d *cub3d)
{
	if (cub3d->map.direct == 'W')
	{
		cub3d->player.dir_x = 0;
		cub3d->player.dir_y = -1;
		cub3d->player.plane_x = -0.66;
		cub3d->player.plane_y = 0;
	}
	else if (cub3d->map.direct == 'E')
	{
		cub3d->player.dir_x = 0;
		cub3d->player.dir_y = 1;
		cub3d->player.plane_x = 0.66;
		cub3d->player.plane_y = 0;
	}
}

void	player_init(t_cub3d *cub3d)
{
	if (cub3d->map.direct == 'N')
	{
		cub3d->player.dir_x = -1;
		cub3d->player.dir_y = 0;
		cub3d->player.plane_x = 0;
		cub3d->player.plane_y = 0.66;
	}
	else if (cub3d->map.direct == 'S')
	{
		cub3d->player.dir_x = 1;
		cub3d->player.dir_y = 0;
		cub3d->player.plane_x = 0;
		cub3d->player.plane_y = -0.66;
	}
	else
		player_init2(cub3d);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

//tüm stractlara değerlerinş atayacağız
void	init_data(t_cub3d *cub3d)
{
	keys_init(cub3d); //key ve mao structlarına değr ver
	player_init(cub3d); //playera ver
}
