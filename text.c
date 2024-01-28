/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:05:20 by mgur              #+#    #+#             */
/*   Updated: 2024/01/26 19:57:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


//çizilen ray'in çarptığı duavrın texture kordinatlarını hesaplar
void	init_text(t_cub3d *cub3d)
{
	double	wallx;

	cub3d->player.text_num = cub3d->map.map[(int)cub3d->player.map_x]
	[(int)cub3d->player.map_y] - 1;
	//bir çıkarmanın nedenini anlaamdık ama herbir x ve y değeri alınıyor ve bunlaın 0 veya 1 değerleri kontrol ediliyor gibi gözüküyor duvar mı boşlık mu
	if (cub3d->player.side == 0) //x ekseninde bir hücre sınırına çarpıyor
		wallx = cub3d->player.pos_y + cub3d->player.perp_wall_dist
			* cub3d->player.raydir_y;
		//çizilen ray'in çaptığı duvarın üzerindeki konumu
	else
		wallx = cub3d->player.pos_x + cub3d->player.perp_wall_dist
			* cub3d->player.raydir_x;
	wallx -= floor(wallx); //wallx değerini ondalık kısmından arındırıp 0 1  arlaığına normalie eder. bu textue de hangi kordinatın kullanılacağını belirler
	cub3d->player.text_x = (int)(wallx * (double)64); //wallx değerine göre texturde hangi  x kordinatının seçileceğini belirler, pixel pixel ilerleme devam
	if (cub3d->player.side == 0 && cub3d->player.raydir_x > 0)
		cub3d->player.text_x = 64 - cub3d->player.text_x - 1; //ğer çizgi dikey bir hücre sınırına çarpıyorsa ve çizgi sağa doğru hareket ediyorsa, textürün sağ yarısını kullanmak için cub3d->player.text_x değeri düzeltilir.
	if (cub3d->player.side == 1 && cub3d->player.raydir_y < 0)
		cub3d->player.text_x = 64 - cub3d->player.text_x - 1; 
	cub3d->player.tex_step = 1.0 * 64 / cub3d->player.line_height; //textur kordinatları arasındaki (birim miktarı) adımı belirler. texture genişliği ile çizilen rayin çarptığı duvarın yükseklik oranı kullanılır
	//meslea textur gen: 64, kordinatlar arası birim miktar 1/64 olur. bu adımda ise bunu çizginin bıyutu(32 olsun mesela)
	//çarparsak 0.5 birim elde ederiz e texturedaki herhangi bir pixel 0.5 birim uzaklıkta demektir	
	cub3d->player.tex_pos = (cub3d->player.draw_start - 1080 / 2
			+ cub3d->player.line_height / 2) * cub3d->player.tex_step;
	//hangş konumdna başlanacağını belirler.perpektif etkiini elde etmek için yapılan heaplamalar.
	//line height:  Çizilen çizginin duvarda kapladığı yüksekliğin yarısıdır. yüksekliği, perspektife bağlı olarak uzaklığa göre değişir
	//Bu ifade, çizilen çizginin ekran üzerindeki konumunu ve yüksekliğini textürdeki birimlere dönüştürür.

}

//bu kordinat bilgileri alınmış texturu bölgesine çizer 
void	text(t_cub3d *cub3d, int x)
{
	int	texty;

	init_text(cub3d);
	while (cub3d->player.draw_start < cub3d->player.draw_end)
	{
		texty = (int)cub3d->player.tex_pos & (64 - 1);
		//& bitwie and operator
		cub3d->player.tex_pos += cub3d->player.tex_step;  //her adımda duvar üzerinde bir çizginin üzerine düşen ışık ışınlarını temsil eder 
		//Güneye Bakış, Pozitif X Yönü: no_data dizisi içinden bir textur belrileme yapar
		if (cub3d->player.side == 0 && cub3d->player.raydir_x > 0)
			cub3d->mlx.addr[cub3d->player.draw_start * cub3d->map.width
				+ x] = cub3d->asset.so_data[64 * texty + cub3d->player.text_x];
		else if (cub3d->player.side == 0 && cub3d->player.raydir_x < 0) //Güneye Bakış, Negatif X Yönü: no_data dizisi içinden bir textur belrileme yapar
			cub3d->mlx.addr[cub3d->player.draw_start * cub3d->map.width
				+ x] = cub3d->asset.no_data[64 * texty + cub3d->player.text_x];
		else if (cub3d->player.side == 1 && cub3d->player.raydir_y > 0) //doğuya Bakış, pozitif y Yönü: ea_data dizisi içinden bir textur belrileme yapar
			cub3d->mlx.addr[cub3d->player.draw_start * cub3d->map.width
				+ x] = cub3d->asset.ea_data[64 * texty + cub3d->player.text_x];
		else //doğuya Bakış, pozitif y Yönü: we_data dizisi içinden bir textur belrileme yapar
			cub3d->mlx.addr[cub3d->player.draw_start * cub3d->map.width
				+ x] = cub3d->asset.we_data[64 * texty + cub3d->player.text_x];
		cub3d->player.draw_start++;
		//Bu if-else blokları, duvarın konumuna ve rayin hareket yönüne bağlı olarak doğru duvar tekstürünü seçerek ekrana çizmeyi sağlar.
	}
}
