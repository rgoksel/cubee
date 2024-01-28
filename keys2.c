/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 02:05:20 by mgur              #+#    #+#             */
/*   Updated: 2024/01/26 20:39:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_left(t_cub3d *cub3d)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = 0.05;
	//burası bakış yönününğ döndürecek olan kısım sola bakamya başalr
	old_dir_x = cub3d->player.dir_x;
	
	cub3d->player.dir_x = cub3d->player.dir_x * cos(rot_speed) \
	- cub3d->player.dir_y * sin(rot_speed);
	
	cub3d->player.dir_y = old_dir_x * sin(rot_speed) \
	+ cub3d->player.dir_y * cos(rot_speed);
	
	//burası kamera düzelimini döndürür. akmera düzlemi de sola doğru döner
	old_plane_x = cub3d->player.plane_x;
	
	cub3d->player.plane_x = cub3d->player.plane_x \
	* cos(rot_speed)- cub3d->player.plane_y * sin(rot_speed);
	
	cub3d->player.plane_y = old_plane_x * sin(rot_speed) \
	+ cub3d->player.plane_y * cos(rot_speed);
}


void	key_right(t_cub3d *cub3d)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = 0.05;
	old_dir_x = cub3d->player.dir_x;
	cub3d->player.dir_x = cub3d->player.dir_x * cos(-rot_speed)
		- cub3d->player.dir_y * sin(-rot_speed);
	cub3d->player.dir_y = old_dir_x * sin(-rot_speed) + cub3d->player.dir_y
		* cos(-rot_speed);
	old_plane_x = cub3d->player.plane_x;
	cub3d->player.plane_x = cub3d->player.plane_x * cos(-rot_speed)
		- cub3d->player.plane_y * sin(-rot_speed);
	cub3d->player.plane_y = old_plane_x * sin(-rot_speed)
		+ cub3d->player.plane_y * cos(-rot_speed);
}