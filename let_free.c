/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgur <mgur@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 21:27:26 by sozbayra          #+#    #+#             */
/*   Updated: 2024/01/15 11:39:53 by mgur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (split[i])
			free(split[i]);
		i++;
	}
	free(split);
}

void	let_free(t_cub3d *cub3d)
{
	if (cub3d->map.ea)
		free(cub3d->map.ea);
	if (cub3d->map.no)
		free(cub3d->map.no);
	if (cub3d->map.so)
		free(cub3d->map.so);
	if (cub3d->map.we)
		free(cub3d->map.we);
}

int	check_for_m2(char **lol)
{
	if (!lol[0] && (lol[2] != NULL && lol[0][0] != 'F' \
	&& lol[0][0] != 'C' && lol[0][0] != '1'))
		return (1);
	else
		return (0);
}
