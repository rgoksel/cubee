/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:42:30 by makbas            #+#    #+#             */
/*   Updated: 2024/02/02 21:08:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render(t_data *data)
{
	prep(data);
	raycast(data);
	key(data);
	return (0);
}

void	key(t_data *cub3d)
{
	if (cub3d->keys->w)
		key_w(cub3d);
	else if (cub3d->keys->s)
		key_s(cub3d);
	else if (cub3d->keys->left)
		key_left(cub3d);
	else if (cub3d->keys->right)
		key_right(cub3d);
	else if (cub3d->keys->d)
		key_d(cub3d);
	else if (cub3d->keys->a)
		key_a(cub3d);
}

/*
görüntüyü hep yok edip tekrar oluşturur ve bu da hem akıcı hem de overloadı engelleryen bir yapı
*/
void	prep(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	mlx_destroy_image(data->screen->mlx, data->screen->img);
	data->screen->img = mlx_new_image(data->screen->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->screen->addr = (int *)mlx_get_data_addr(data->screen->img, \
		&data->screen->bpp, &data->screen->size_line, &data->screen->endian);
	while (y < WIN_WIDTH)
	{
		x = 0;
		while (x < WIN_HEIGHT)
		{
			if (x < WIN_HEIGHT / 2)
				data->screen->addr[x * WIN_WIDTH + y] = data->screen->ceiling;
			else
				data->screen->addr[x * WIN_WIDTH + y] = data->screen->floor;
			x++;
		}
		y++;
	}
}


/* 
[-1, 1] aralığında virgüllü değerleri cameranınn x değernine veriyor
camera_x bir yatay çizginin ekranda nereye çizileceğini belirtir
-1 en sol +1 en sağ
raydir_x = ışın yönü (vektörü):  genellikle kamera pozisyonu, bakış açısı ve projeksiyon düzleminin bir fonksiyonu olarak hesaplanır
bu vektröler playerın yönünün vektörü nokta olarak alınır, kameranın [-1, 1] arasındaki değerleri ile plane değerleri çarpılır ve bu da her bir noktanın vektörünü verir
*/

void	raycast(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->screen->width))
	{
		data->ray->camera_x = 2 * i / (double)data->screen->width - 1;
		data->ray->raydir_x = data->player->dir_x + data->player->plane_x
			* data->ray->camera_x;
		data->ray->raydir_y = data->player->dir_y + data->player->plane_y
			* data->ray->camera_x;
		data->ray->map_x = (int)data->player->pos_x;
		data->ray->map_y = (int)data->player->pos_y;
		raycast2(data, i);
		i++;
	}
	mlx_put_image_to_window(data->screen->mlx, data->screen->mlx_win,
		data->screen->img, 0, 0); //bunu kaldırırsak nolur? aynı şeyi ekrana basıp duruyo ikinici ke çünkü gerek var mı
}


/* 
sınır : bire birik ir kareli kağıdın çizgilerini varsay
raydir_x = 0 paralellik mevcut x eksneinde hiçbirşey kesmeyecek, sıfır değilse 
çizginin x eksenine göre bir birimlik adımının bir hücre sınırına ulaşması için gereken mesafeyi bulur.
delta_dist_x = 3d sahnede çizilen rayin bir sınıra çarpmması için gerken uzaklık
*/

void	raycast2(t_data *data, int i)
{
	if (data->ray->raydir_x == 0)
		data->ray->delta_dist_x = 1e30;
	else
		data->ray->delta_dist_x = fabs(1 / data->ray->raydir_x);
	if (data->ray->raydir_y == 0)
		data->ray->delta_dist_y = 1e30;
	else
		data->ray->delta_dist_y = fabs(1 / data->ray->raydir_y);
	dir(data);
	hit(data);
	dist(data);
	text(data, i);
}

/*
 hareket yönü ve sınırlara olan uzaklığı bulur

*/

void	dir(t_data *data)
{
	if (data->ray->raydir_x < 0) // çizgiler sola doğrı demek \ böyle gibi...
	{
		data->ray->step_x = -1; //adım şeklini eksi bir ayarla
		data->ray->side_dist_x = (data->player->pos_x - data->ray->map_x) * data->ray->delta_dist_x;
		//side dist_x :sol tarafta herhangi bir sınıra olan uzaklık
	}
	else
	{
		data->ray->step_x = 1;
		data->ray->side_dist_x = (data->ray->map_x + 1 - data->player->pos_x) * data->ray->delta_dist_x;
	}
	if (data->ray->raydir_y < 0)
	{
		data->ray->step_y = -1;
		data->ray->side_dist_y = (data->player->pos_y - data->ray->map_y)
			* data->ray->delta_dist_y;
	}
	else
	{
		data->ray->step_y = 1;
		data->ray->side_dist_y = (data->ray->map_y + 1 - data->player->pos_y) * data->ray->delta_dist_y;
	}
}


/*
çizilen herhangi bir ışın bir hücre ınırına çarptı mı çarpmadı mı kontolü
delta bir birimlik adım atması için gereken mesafeyi ifade eder ve side_dist_x değerini onu ekleyerke 
bir adım attın diyelim yeni mesafenin uzaklığı güncellendi gibi gibi..
en sonda duvara vurdu mu kontolü
*/
void	hit(t_data *data)
{
	data->ray->hit = 0;
	while (data->ray->hit == 0)
	{
		if (data->ray->side_dist_x < data->ray->side_dist_y)
		{
			data->ray->side_dist_x += data->ray->delta_dist_x;
			data->ray->map_x += data->ray->step_x;
			data->ray->side = 0;
			// side = 0 => x eksenine çaptığını ifade ediyor. ayrıca durvar yönünü de gösteecek
		}
		else
		{
			data->ray->side_dist_y += data->ray->delta_dist_y;
			data->ray->map_y += data->ray->step_y;
			data->ray->side = 1;
			//1 ise y ekseninde hücre sınırına çarptığını ve dolayısıyla üst veya alt yüzeyini kesitğini gösterir.

		}
		if (data->map[(int)data->ray->map_x][(int)data->ray->map_y] == '1')
			data->ray->hit = 1;
	}
}

/*
çizginin çarptığı duvarın uzaklığı, çizginin ekran alt üst kenarları arasındaki yüksekliğini ve çizilecek
olan duvarın ekran üzerindkei başlangıç ve bitiş noktaları hesaplanır

if else bloğunda duvarın  uzaklığı hesaplanır. side değerine göre çizginin
x ekseninde mi yoksa y ekseninde mi bir sonraki hücre sınırına geçtiğini kontrol eder.
çizilen ışığın x ekseninde bir sonraki hücre sınırına olan dik mesafeyi hesaplar.
delta: hher br hücrenin kenar uzunnlğu 
side_dist: çizginin o anki konumundan x eksenindeki bir sonraki hücre sınırna dik uzaklığı
*/
void	dist(t_data *data)
{
	if (data->ray->side == 0)
		data->ray->perp_wall_dist = data->ray->side_dist_x
			- data->ray->delta_dist_x;
	else
		data->ray->perp_wall_dist = data->ray->side_dist_y
			- data->ray->delta_dist_y; //balık gözü efektini engelemke için hemde tam sayılarla uğraşmak için olduğunu varsayıyorum.
	data->ray->line_height = (int)(1080 / data->ray->perp_wall_dist);  //duvarda kaplaması gereken alan bulunuyor.
	data->ray->draw_start = -data->ray->line_height / 2 + 1080 / 2;   //nereden itibaren duvar çizilmeye başlanacak belirleniyor
	if (data->ray->draw_start < 0)
		data->ray->draw_start = 0; // ekranın altından başlasın çzimeye
	data->ray->draw_end = data->ray->line_height / 2 + 1080 / 2; //nerede bitecek duvar
	if (data->ray->draw_end >= 1080)
		data->ray->draw_end = 1080 - 1;
}


//çizilen ray'in çarptığı duavrın texture kordinatlarını hesaplar
void	init_text(t_data *data)
{
	double	wallx;

	data->ray->text_num = data->map[(int)data->ray->map_x]
	[(int)data->ray->map_y] - 1;
	if (data->ray->side == 0)
		wallx = data->player->pos_y + data->ray->perp_wall_dist
			* data->ray->raydir_y;
	else
		wallx = data->player->pos_x + data->ray->perp_wall_dist
			* data->ray->raydir_x;
	wallx -= floor(wallx);
	data->ray->text_x = (int)(wallx * (double)256);
	//texture koordinatlarını düzeltme işlemleridir. Bu, özellikle ışının ters yönde ilerlediği durumları düzeltmeye yöneliktir.
	if (data->ray->side == 0 && data->ray->raydir_x > 0)
		data->ray->text_x = 256 - data->ray->text_x - 1;
	if (data->ray->side == 1 && data->ray->raydir_y < 0)
		data->ray->text_x = 256 - data->ray->text_x - 1;
	data->ray->tex_step = 1.0 * 256 / data->ray->line_height;
	//1, //textur kordinatları arasındaki (birim miktarı) adımı belirler. texture genişliği ile çizilen rayin çarptığı duvarın yükseklik oranı kullanılır
	data->ray->tex_pos = (data->ray->draw_start - 1080 / 2
			+ data->ray->line_height / 2) * data->ray->tex_step;
	//hangş konumdna başlanacağını belirler.perpektif etkiini elde etmek için yapılan heaplamalar.
	//line height:  Çizilen çizginin duvarda kapladığı yüksekliğin yarısıdır. yüksekliği, perspektife bağlı olarak uzaklığa göre değişir
	//Bu ifade, çizilen çizginin ekran üzerindeki konumunu ve yüksekliğini textürdeki birimlere dönüştürür.
}

//bu kordinat bilgileri alınmış texturu bölgesine çizer 
//Bu if-else blokları, duvarın konumuna ve rayin hareket yönüne bağlı olarak doğru duvar tekstürünü seçerek ekrana çizmeyi sağlar.
void	text(t_data *data, int x)
{
	int	texty;

	init_text(data);
	while (data->ray->draw_start < data->ray->draw_end)
	{
		//gelen değeri integara çevirip 256 ile mod alma gibi bi işlem, 255den büyükse başa dönüyor
		texty = (int)data->ray->tex_pos & (256 - 1);
		//her adımda duvar üzerinde bir çizginin üzerine düşen ışık ışınlarını temsil eder 
		data->ray->tex_pos += data->ray->tex_step;
		
		//Güneye Bakış, Pozitif X Yönü: no_data dizisi içinden bir textur belrileme yapar
		if (data->ray->side == 0 && data->ray->raydir_x > 0)
			data->screen->addr[data->ray->draw_start * data->screen->width
				+ x] = data->wall[SOUTH].addr[256 * texty + data->ray->text_x];
		else if (data->ray->side == 0 && data->ray->raydir_x < 0) //Güneye Bakış, Negatif X Yönü: no_data dizisi içinden bir textur belrileme yapar
			data->screen->addr[data->ray->draw_start * data->screen->width
				+ x] = data->wall[NORTH].addr[256 * texty + data->ray->text_x]; 
		else if (data->ray->side == 1 && data->ray->raydir_y > 0) //doğuya Bakış, pozitif y Yönü: ea_data dizisi içinden bir textur belrileme yapar
			data->screen->addr[data->ray->draw_start * data->screen->width
				+ x] = data->wall[EAST].addr[256 * texty + data->ray->text_x];
		else //doğuya Bakış, pozitif y Yönü: we_data dizisi içinden bir textur belrileme yapar
			data->screen->addr[data->ray->draw_start * data->screen->width
				+ x] = data->wall[WEST].addr[256 * texty + data->ray->text_x];
		data->ray->draw_start++;
	}
}