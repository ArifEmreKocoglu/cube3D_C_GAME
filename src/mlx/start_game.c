/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:48:28 by eayyildi          #+#    #+#             */
/*   Updated: 2023/05/02 22:38:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_c_rgb(t_data *data)
{
	int		x;
	int		y;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		// Bu kod parçası, verilen üç tam sayı değeri (r, g ve b) ile temsil edilen bir RGB renk kodunu hesaplamak için kullanılır.
		while (++y < WIN_HEIGHT / 2)
			data->screen_img_data[y * WIN_WIDTH + x] = \
				rbg_to_int(data->c_rgb[0], data->c_rgb[1], \
					data->c_rgb[2]);
	}
}

void	print_f_rgb(t_data *data)
{
	int		x;
	int		y;

	x = 0;
	y = WIN_HEIGHT / 2;
	while (x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		data->screen_img_data[y * WIN_WIDTH + x] = \
			rbg_to_int(data->f_rgb[0], data->f_rgb[1], \
				data->f_rgb[2]);
		x++;
		if (x == WIN_WIDTH)
		{
			y++;
			x = 0;
		}
	}
}

int	put_image(t_data *data)
{
	int		i;
	void	*img_ptr;

	data->imgs_data = (int **)malloc(sizeof(int *) * 4); // 4 tane resim olduğu için kuzey guney dogu batı
	i = -1;
	while (++i < 4)
	{
		img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->imgs[i], \
		&data->img_x, &data->img_y); // xmp uzantılı resimleri okur ve bir pointer döndürür (dönen pointeri ekrana basması için mlx_put_image_to_window() fonksiyona parametre olarak yollucağız)
		//Parametre olarak mlx_ptr, xpm dosyasının konumu ve iki tane değeri verilmemiş int adresi veriyoruz. Eğer okuyamazsa null döndürür. Resimler genellikle png veya jpg
		//olur xpm çevirmek için bu siteyi kullanabilirsiniz: https://convertio.co/tr/png-xpm/
		if (img_ptr == NULL)
			return (print_error("xpm file path is invalid."));
		data->imgs_data[i] = (int *)mlx_get_data_addr(img_ptr, \
			&data->bits_per_pixel, &data->size_line, &data->endian);
	}
	return (0);
}

int	key_press(int key, t_data *data) // raycasting
{
	key_press_helper(data, key);
	key_press_helper2(data, key);
	key_press_helper3(data, key);
	if (key == ESC)
		ft_exit(data);
	print_c_rgb(data);
	print_f_rgb(data);
	print_map(data);
	return (0);
}

int	start_game(t_data *data)
{
	data->move_speed = 0.2; // oyuncu hareket hızı
	data->rot_speed = 0.2; // oyuncu dönüs hızı
	data->mlx_ptr = mlx_init(); // Minilibx kütüphanesini başlatır ve void bir pointer döndürür. Dönen void pointerı
	// neredeyse kütüphanenin tüm fonksıyonlara parametre olarak yolluyoruz.
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, \
	WIN_HEIGHT, "Cub3D"); // Siyah içi boş bir pencere oluşturur. Parametre olarak mlx_ptr, pencerenin genişliği için int width,
	// yüksekliği için int height ve son olarak pencere adı alır(const char bir dizi olarak)
	// Daha sonra fonksiyon bize void bir win_ptr pointer döndürür. mlx_ptr gibi hemen hemen kütüphanenin tüm fonksiyonlara
	// parametre olarak yolluyoruz.
	data->screen_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT); // İçi boş(siyah) resim oluşturur parametre olarak mlx_ptr, oluşacak resim genişligi(width) ve oluşacak resmin yüksekliği (height) alır. 
    // Eger resmi başarılı bir şekilde oluştursa bize void *img_ptr döndürür.
	data->screen_img_data = (int *)mlx_get_data_addr(data->screen_img, \
	&data->bits_per_pixel, &data->size_line, &data->endian); // Diyelimki bir resim oluşturduk peki resmin içindeki pixellere nasıl ulaşıcaz içini nasıl doldurcaz hepsini mlx_get_data_addr fonksiyondan 
	//dönen int diziden yapıyoruz bu fonksiyon hem bir resim hakkında bilgi verir hemde resmin pixel pixel datasını bize int dizi olarak döndürür.Öncelikle
	//parametre olarak resmin adresini alır(img_ptr), daha sonra bu resim hakkında bilgilerini gelen parametrelerın ıcıne aktarmak için bits_per_pixel,
	//size_line ve endian degişkenlerinin (3 de int türünden olmalı) adresslerini gönderiyoruz(basına & koyarsanız o degişkenin adresini göndermiş oluruz)
	//daha sonra bize dönen int *img_data nın diyelimki 0. pixel renk kodunu kırmızı yapıcaz yapıcagımız işlem şu: img_data[0] = FF0000; eger resmin full
	//kırmızı olmasını ıstıyorsak whıle ile içini donup tek tek pıxel koduna kırmızı degerini vermemız gerekırdı.
	if (put_image(data))
	{
		ft_free_helper(data);
		return (1);
	}
	print_c_rgb(data); // ceiling tavan için renklendirme işlemi rgb sayılarıyla
	print_f_rgb(data); // floor zemin için renklendirme işlemi rgb sayılarıyla
	print_map(data); // raycasting sonra bakılacak
	mlx_hook(data->win_ptr, 2, 1L << 0, &key_press, data); // Klayveyi kontrol eder parametre olarak win_ptr, "2, 1L << 0" değerleri sabit ve
	//int döndüren int bir parametre alan (çünkü klayvede basılan her tuşun int bir karşılığı var bunları fonksiyon içinde kontrol etmek için)
	//fonksiyon, bide bu fonksiyonun kaynagını veriyoruz(yukardaki açıklamayla aynı ek olarak dıyelımkı fonksıyon dısardan herhangı bır kaynak parametre almıyorsa
	//NULL yazıyoruz)
	mlx_hook(data->win_ptr, 17, 0, (void *)ft_exit, data); // Pencereden çarpı(x) butonunu kontrol eder parametre olarak win_ptr,
	//"17, 0" degerleri sabit, int döndüren bir fonksiyon ve bir sonraki parametre ise önceki parametre olarak verdigimiz 
	//fonksiyonun parametresini veriyoruz
	mlx_loop(data->mlx_ptr); // Pencerenin açık kalmasını sağlar. Parametre olarak mlx_ptr alır.
	return (0);
}
