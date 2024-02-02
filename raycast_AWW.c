/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 21:37:06 by sozbayra          #+#    #+#             */
/*   Updated: 2024/01/31 17:31:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
 
//hareket yönü ve sınırlar uzaklık belirlemek için kullanılır
void	dir(t_cub3d *cub3d)
{
	if (cub3d->player.raydir_x < 0) // çizgiler sola doğru demektir. burada step_x'e -1 verekrek bir belirteç gibi kullanıyoruz
	{
		cub3d->player.step_x = -1;
		cub3d->player.side_dist_x = (cub3d->player.pos_x - cub3d->player.map_x)
			* cub3d->player.delta_dist_x;
		//pos_x - map_x ise çiginin mevcudu ile sınırı arasındai mesafe
		//çizginin x eksininde bir birimlik adımının bir hücre sınırına ulaşması için geken mesafeyi gösterir
	}
	else
	{
		cub3d->player.step_x = 1;
		//bu +1 değerleri yuverlamadan dolayı oluşan bi saçmalıkmış sanırım. mesela
		//çizginin mevcut x konumu 2.3 olsun. Budurumda, map_x ifadesi 2 olacaktır çünkü çizginin olduğu hücrenin x'i 2 dir. ama bir sonraki hücresınırının x'i 3 olacaktır.
		//+1, çizginin bir hücre sınırından diğerine geçişi temsil eder
		cub3d->player.side_dist_x = (cub3d->player.map_x + 1
				- cub3d->player.pos_x) * cub3d->player.delta_dist_x;
	}
	if (cub3d->player.raydir_y < 0)
	{
		cub3d->player.step_y = -1;
		cub3d->player.side_dist_y = (cub3d->player.pos_y - cub3d->player.map_y)
			* cub3d->player.delta_dist_y;
	}
	else
	{
		cub3d->player.step_y = 1;
		cub3d->player.side_dist_y = (cub3d->player.map_y + 1
				- cub3d->player.pos_y) * cub3d->player.delta_dist_y;
	}
}

//çizilen bir ray hücre sınırına çarptı  mı çarpmadı mı  kontrolu 
void	hit(t_cub3d *cub3d)
{
	cub3d->player.hit = 0; //structa değer atayıp beklyorzu ve bir değer artışı olaan kadar döngü devm edecek
	while (cub3d->player.hit == 0)
	{
		if (cub3d->player.side_dist_x < cub3d->player.side_dist_y)
		{
			//side_dist_x ve y bir hücre sınırına (aga bu arad hücre sınırı bir kordinatlarda tam sayı değerlerine sahip her bir noktayı ifeda ediyor) uzaklığı ifade ediyor
			//
			cub3d->player.side_dist_x += cub3d->player.delta_dist_x; ///delta bir birimlik adım atması için gereken mesafeyi ifade eder ve side_dist_x değerini onu ekleyerke 
			// bir adım attın diyelim yeni mesafenin uzaklığı güncellendi gibi gibi..
			cub3d->player.map_x += cub3d->player.step_x; //step_x ve step_y hareket yönelrini belirleyen-1 ve 1 eğerleriydi ve map_x knumunu buna göre güncelliyor
			cub3d->player.side = 0; //hangş eksen tarafındna kesildiğini ifade eden bir belirteç, x için 0 seçlmiş bla bla
			//0 ise x ekseninde hücre sınırına çarptığını gösterir.
			//duvarın hangi yönde olduğunu gösterir.
		}
		else
		{
			cub3d->player.side_dist_y += cub3d->player.delta_dist_y;
			cub3d->player.map_y += cub3d->player.step_y;
			cub3d->player.side = 1;
			//1 ise y ekseninde hücre sınırına çarptığını ve dolayısıyla üst veya alt yüzeyini kesitğini gösterir.
		}
		if (cub3d->map.map[(int)cub3d->player.map_x]
			[(int)cub3d->player.map_y] == '1') // çzgin ulaştığı hücre sınırının harita üzerindeki değeri kontol edilir. u değer bir sie vurdu anlamına gelir ve döngü biter adım adım yapılan resimdeki işlemmiş yani
			cub3d->player.hit = 1;
			
	}
}


//en önemli fonksion, önceki fonksiyonda duvara çarpma olmadığı zmaanalrda side_dist_x değerlerine falan atamalar yaptık.
//şimdi çizginin çarptığı duvarın uzaklığı, çizginin ekran alt üst kenarları arasındaki yüksekliğini ve çizilecek
//olan duvarın ekran üzerindkei başlangıç ve bitiş noktaları hesaplanır. 
void	dist(t_cub3d *cub3d)
{
	//if else bloğunda duvarın  uzaklığı hesaplanır. side değerine göre çizginin x ekseninde mi yoksa y ekseninde mi bir sonraki hücre sınırına geçtiğini kontrol eder.
	//çizilen ışığın x ekseninde bir sonraki ücre sınırına olan dik mesafeyi hesaplar.
	//delta: hher br hücrenin kenar uzunnlğu 
	//side_dist: çizginin o ankş konumundan x eksenindeki bir sonraki hücre sınırna dik uzaklığı
	if (cub3d->player.side == 0) //ray x ekseninde bir hücre sınırına çarpıyor. 
		cub3d->player.perp_wall_dist = cub3d->player.side_dist_x
			- cub3d->player.delta_dist_x; //perpendicular wall distance. çizilen rayin çarptığı duvarın dik mesafesini ifade eder.
	else
		cub3d->player.perp_wall_dist = cub3d->player.side_dist_y
			- cub3d->player.delta_dist_y;
	cub3d->player.line_height = (int)(1080 / cub3d->player.perp_wall_dist);
	//1080 ile oranlayarak yüksekliğini bulacak. duvaın ekrandaki yüksekliği. perp_wall arttıkça line height küçülecek
	cub3d->player.draw_start = -cub3d->player.line_height / 2 + 1080 / 2;
	//duvarın ekran üzerindeki başlama noktasını bulur. 1080 ekran yüksekliğiydi
	if (cub3d->player.draw_start < 0)
		cub3d->player.draw_start = 0;
	//duvara çok yakınsan tüm ekran duvar olacak
	cub3d->player.draw_end = cub3d->player.line_height / 2 + 1080 / 2;
	//duvarın tepe noktasının ekrandaki yerş
	if (cub3d->player.draw_end >= 1080)
		cub3d->player.draw_end = 1080 - 1;
		//duvara çok yakınsan tüm ekran duvar olacak

}

void	key(t_cub3d *cub3d)
{
	if (cub3d->keys.w)
		key_w(cub3d);
	else if (cub3d->keys.s)
		key_s(cub3d);
	else if (cub3d->keys.left)
		key_left(cub3d);
	else if (cub3d->keys.right)
		key_right(cub3d);
	else if (cub3d->keys.d)
		key_d(cub3d);
	else if (cub3d->keys.a)
		key_a(cub3d);
}

void	raycast(t_cub3d *cub3d)
{
	int	i;

	i = 0; //yatay bir şekilde ekranı tarıyor
	while (i < (cub3d->map.width))
	{
		//[-1, 1] aralığında oynayan virgüllü değerleri cameranınn x değernine veriyor
		cub3d->player.camera_x = 2 * i / (double)cub3d->map.width - 1;
		//camera_x bir yatay çizginin ekranda nereye çizileceğini belrtmek için kullanılan bir dğer. -1 ekraın solunu,
		//+1 ise ekranın en sağını ifade eder bu br normalize işlemidir. bu değer ile döngü boyunca cizilecek her bir çzgi belirlenir. 
		
		cub3d->player.raydir_x = cub3d->player.dir_x + cub3d->player.plane_x
			* cub3d->player.camera_x;
		cub3d->player.raydir_y = cub3d->player.dir_y + cub3d->player.plane_y
			* cub3d->player.camera_x;	
		//raydir - raydirection: raycastingde kullanılan bir vektördür. 3d sahne 2d bir düzleme yansıtılır ve her bir ray belrli bir yönü temsil eder. br noktadan belirli bir yöne giden bi rçizgiyi ifade edr 
		//Raydir vektörleri genellikle kamera pozisyonu, bakış açısı ve projeksiyon düzleminin bir fonksiyonu olarak hesaplanır.
		//her bir pixelin 3d deki  bir noktaya  bağlayan çizgileri ifade eder.
		//so, raydir_x ve raydir_y bir notadan görüntü düzeleminin her bir noktasına giden rayin yönünü temsil eden vektrölerdir
		//bu vektröler playerın yönünün vektörü nokta olarak alınırken kameranın -1 ve 1 ddeğerleri arasından oynayan değerşeri ile plane eğerleri çarpılır ve bu da her bir noktanın vektörünü verir.
		cub3d->player.map_x = (int)cub3d->player.pos_x;
		cub3d->player.map_y = (int)cub3d->player.pos_y;
		//playeırn kendi konumunu da daha sonra kulllanmak için map_x değerlerine atıyoruz.
		raycast2(cub3d, i); //her bir i değerini de bu fonksiyona structla beraber göndercez
		//i değerine baplı olarak camera değeri ve n-buna bağlı olarak ray_Dir x ve ray_dir_y değerleri hesaplanıe
		i++;
	}
	mlx_put_image_to_window(cub3d->mlx.init, cub3d->mlx.win,
		cub3d->mlx.object, 0, 0);
}
