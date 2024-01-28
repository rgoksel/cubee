/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:46:32 by mgur              #+#    #+#             */
/*   Updated: 2024/01/26 20:19:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//ileri yönde gidiş
void	key_w(t_cub3d *cub3d)
{
	float	move_speed;

	move_speed = 0.05;
	//x ekseninde hareket için if bloğu koyulmuş, geçilebilri bir alan ve başka bir oyunc yoksa 
	if (cub3d->map.map[(int)(cub3d->player.pos_x + cub3d->player.dir_x
			* move_speed)][(int)(cub3d->player.pos_y)] == '0'
		|| is_player(cub3d->map.map[(int)(cub3d->player.pos_x
				+ cub3d->player.dir_x
				* move_speed)][(int)(cub3d->player.pos_y)])) // is player ksımı çok oyunculu durumlar için varmış silebileriz deneriz
		cub3d->player.pos_x += cub3d->player.dir_x * move_speed;
	if (cub3d->map.map[(int)(cub3d->player.pos_x)][(int)(cub3d->player.pos_y
			+ cub3d->player.dir_y * move_speed)] == '0'
		|| is_player(cub3d->map.map[(int)(cub3d->player.pos_x)]
		[(int)(cub3d->player.pos_y
				+ cub3d->player.dir_y * move_speed)]))
		cub3d->player.pos_y += cub3d->player.dir_y * move_speed;
}

//geri gidiş
void	key_s(t_cub3d *cub3d)
{
	float	move_speed;

	move_speed = 0.05;
	if (cub3d->map.map[(int)(cub3d->player.pos_x - cub3d->player.dir_x
			* move_speed)][(int)(cub3d->player.pos_y)] == '0'
		|| is_player(cub3d->map.map[(int)(cub3d->player.pos_x
				- cub3d->player.dir_x
				* move_speed)][(int)(cub3d->player.pos_y)]))
		cub3d->player.pos_x -= cub3d->player.dir_x * move_speed;
	if (cub3d->map.map[(int)(cub3d->player.pos_x)][(int)(cub3d->player.pos_y
			- cub3d->player.dir_y * move_speed)] == '0'
		|| is_player(cub3d->map.map[(int)cub3d->player.pos_x]
		[(int)(cub3d->player.pos_y
				- cub3d->player.dir_y * move_speed)]))
		cub3d->player.pos_y -= cub3d->player.dir_y * move_speed;
}

//sağa gidiyo pff
void	key_d(t_cub3d *cub3d)
{
	float	move_speed;

	move_speed = 0.05;
	if (cub3d->map.map[(int)(cub3d->player.pos_x + cub3d->player.dir_y
			* move_speed)][(int)(cub3d->player.pos_y)] == '0'
		|| is_player(cub3d->map.map[(int)(cub3d->player.pos_x
				+ cub3d->player.dir_y
				* move_speed)][(int)(cub3d->player.pos_y)]))
		cub3d->player.pos_x += cub3d->player.dir_y * move_speed;
	if (cub3d->map.map[(int)(cub3d->player.pos_x)][(int)(cub3d->player.pos_y
			- cub3d->player.dir_x * move_speed)] == '0'
		|| is_player(cub3d->map.map[(int)cub3d->player.pos_x]
		[(int)(cub3d->player.pos_y
				- cub3d->player.dir_x * move_speed)]))
		cub3d->player.pos_y -= cub3d->player.dir_x * move_speed;
}


//sola gidiyo wtf
void	key_a(t_cub3d *cub3d)
{
	float	move_speed;

	move_speed = 0.05;
	if (cub3d->map.map[(int)(cub3d->player.pos_x - cub3d->player.dir_y
			* move_speed)][(int)(cub3d->player.pos_y)] == '0'
		|| is_player(cub3d->map.map[(int)(cub3d->player.pos_x
				- cub3d->player.dir_y
				* move_speed)][(int)(cub3d->player.pos_y)]))
		cub3d->player.pos_x -= cub3d->player.dir_y * move_speed;
	if (cub3d->map.map[(int)(cub3d->player.pos_x)][(int)(cub3d->player.pos_y
			+ cub3d->player.dir_x * move_speed)] == '0'
		|| is_player(cub3d->map.map[(int)cub3d->player.pos_x]
		[(int)(cub3d->player.pos_y
				+ cub3d->player.dir_x * move_speed)]))
		cub3d->player.pos_y += cub3d->player.dir_x * move_speed;
}

//

