/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:58:33 by mgur              #+#    #+#             */
/*   Updated: 2024/01/26 12:05:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_xpm(t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = 64;
	y = 64;
	cub3d->asset.i_no = mlx_xpm_file_to_image(cub3d->mlx.init, cub3d->map.no,
			&x, &y); //xpm dosyalarını mapte atama yaptıktan sonra göünütde verilecek ama anlamadığım şey şuan burası null ne mana atayacağızz
	cub3d->asset.no_data = (int *)mlx_get_data_addr(cub3d->asset.i_no,
			&cub3d->asset.no_b, &cub3d->asset.no_size_line,
			&cub3d->asset.no_endian); //oluşan imageın o yöndeki bir bitinn büyüklüğü, bir lineın uzunluğu ve bellekteki sıra düzeninden o yöndeki eklene imageın adresini bize verir ve bunu structın no_data verisinde tutar
	cub3d->asset.i_so = mlx_xpm_file_to_image(cub3d->mlx.init, cub3d->map.so,
			&x, &y);
	cub3d->asset.so_data = (int *)mlx_get_data_addr(cub3d->asset.i_so,
			&cub3d->asset.so_b, &cub3d->asset.so_size_line,
			&cub3d->asset.so_endian);
	cub3d->asset.i_we = mlx_xpm_file_to_image(cub3d->mlx.init, cub3d->map.we,
			&x, &y);
	cub3d->asset.we_data = (int *)mlx_get_data_addr(cub3d->asset.i_we,
			&cub3d->asset.we_b, &cub3d->asset.we_size_line,
			&cub3d->asset.we_endian);
	cub3d->asset.i_ea = mlx_xpm_file_to_image(cub3d->mlx.init, cub3d->map.ea,
			&x, &y);
	cub3d->asset.ea_data = (int *)mlx_get_data_addr(cub3d->asset.i_ea,
			&cub3d->asset.ea_b, &cub3d->asset.ea_size_line,
			&cub3d->asset.ea_endian);
}

//her an görüntüyü yok edip tekrar oluşturarak bir başlangıç yapıyoruz. şuan tamamen üzerine birşey eklenmemiş version ile uğraşıyoruz ı guess. üzerine birşey eklenmiş ve dataları alınmış şeyler assetde duruyor
void	prep(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	mlx_destroy_image(cub3d->mlx.init, cub3d->mlx.object);
	cub3d->mlx.object = mlx_new_image(cub3d->mlx.init, cub3d->map.width,
			cub3d->map.height);
	cub3d->mlx.addr = (int *)mlx_get_data_addr(cub3d->mlx.object,
			&cub3d->mlx.bits_per_pixel, &cub3d->mlx.line_length,
			&cub3d->mlx.endian);
			
	//bu döngüde ise ekranı yarıdan bölüp c ve f değerlerin pixel değerlerini koyuyoz
	while (i < cub3d->map.width)
	{
		j = 0;
		while (j < cub3d->map.height)
		{
			if (j < cub3d->map.height / 2)
				cub3d->mlx.addr[j * cub3d->map.width + i] = cub3d->map.c;
			else
				cub3d->mlx.addr[j * cub3d->map.width + i] = cub3d->map.f;
			j++;
		}
		i++;
	}
}

//mlx_loop_hook ile hep çalışacak fonksiyonlar
int	render(t_cub3d *cub3d)
{
	prep(cub3d);
	raycast(cub3d);
	key(cub3d);
	return (0);
}

int	close_window(t_cub3d *cub3d)
{
	mlx_destroy_window(cub3d->mlx.init, cub3d->mlx.win);
	exit(0);
}

int	key_press(int keycode, t_cub3d *cub3d)
{
	if (keycode == 53)
	{
		let_free(cub3d);
		exit(0);
	}
	if (keycode == 13)
		cub3d->keys.w = 1;
	if (keycode == 0)
		cub3d->keys.a = 1;
	if (keycode == 1)
		cub3d->keys.s = 1;
	if (keycode == 2)
		cub3d->keys.d = 1;
	if (keycode == 123)
		cub3d->keys.left = 1;
	if (keycode == 124)
		cub3d->keys.right = 1;
	return (0);
}
