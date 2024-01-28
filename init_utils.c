/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:12:52 by mgur              #+#    #+#             */
/*   Updated: 2024/01/25 15:04:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//this is for map name
int	check_cub(char *str)
{
	int	len;
	int	fd;

	fd = open(str, O_RDONLY);
	len = strlen(str);
	if (str[--len] == 'b' && str[--len] == 'u' && str[--len] == 'c' \
	&& str[--len] == '.' && fd > 0)
	{
		close(fd);
		return (0);
	}
	else
	{
		close(fd);
		printf("incorrect file extension\n");
		exit(1);
	}
}

//struct yapısında bir harita methodu gözetilmiş. 
//en ortadaki ana structın adı cube3d iken içinde yer alan map structının 
//elemanlarının değerlerinin atanması ve başlatılması burada gerçekleştriliyor.
void	init_map(t_fm *map)
{
	map->check = 0;
	map->f = -1; //yer ve gök
	map->c = -1;
	map->height = 1080; //sanırım burda tüm ekranı kaplaması için değerleri böyle verdik
	map->width = 1920;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->direct = 'G'; //player initilize ederken kullanmışız bunu sanırım değiştirilebilir bir dğeere sahip, wens değerleinn birine sahip olmalı aam niye böyle g deeğri var wtf
}

void	init_free(t_fm *map)
{
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
}

int	for_f(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'F' || str[i] == 'C')
			return (++i);
		i++;
	}
	return (0);
}

int	is_just_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		printf("%d\n",str[i]);
		exit(1);
		if (str[i] != ' ' || str[i] != 0)
			return (1);
	}
	return (0);
}
