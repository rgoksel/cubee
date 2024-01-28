/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgur <mgur@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:41:29 by mgur              #+#    #+#             */
/*   Updated: 2024/01/15 10:41:29 by mgur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)malloc(sizeof(t_cub3d));
	if (argc != 2 || check_cub(argv[1]))
	{
		printf("input error\n");
		exit(1);
	}
	init_map(&cub3d->map);
	check_map(argv[1], &cub3d);
	init_data(cub3d);
	start_render(cub3d);
	return (0);
}
