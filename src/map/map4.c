/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:48:10 by eayyildi          #+#    #+#             */
/*   Updated: 2023/05/03 11:31:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	setup_int_map3(t_data *data)
{
	int		i;
	int		x;
	int		y;

	i = -1;
	x = 0;
	y = 0;
	while (data->map2[++i])
	{
		if (data->map2[i] == '\n')
		{
			x = -1;
			y++;
		}
		else if (data->map2[i] != '\t' && data->map2[i] != ' ')
			int_map_helper(data, i, x, y);// OYUNCUNUN X VE Y NOKTASINDAKİ KONUMUNU BULUR. map3 e oyunucunun konumu ve yönü int deer olarak atıldı.
		x++;
	}
}

void	setup_int_map2(t_data *data, int map_width, int map_height)
{
	int		i;
	int		j;

	i = -1;
	data->map3 = (int **)malloc(sizeof(int *) * map_width);
	while (++i < map_width)
		data->map3[i] = (int *)malloc(sizeof(int) * map_height);
	i = -1;
	while (++i < map_width)
	{
		j = -1;
		while (++j < map_height)
			data->map3[i][j] = 0;
	}
	setup_int_map3(data);// OYUNCUNUN X VE Y KONUMUNU BULUR. // burada map3 ün konumunu int deer olarak diziye ekledik artık oyuncunun konumunu ve yönünü biliyoruz.
}

int	ft_strlen_mod(char *array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		if (array[i] == '\t')
			i += TAB_SIZE;
		else
			i++;
	}
	return (i);
}

int	check_max_number(char **array, int number, int skip)
{
	int		i;

	i = -1;
	while (array[++i])
		if (number < (int)ft_strlen_mod(array[i]) && i != skip)
			return (-1);
	return (1);
}

int	setup_int_map(t_data *data)
{
	char	**array;
	int		i;
	int		map_width;
	int		map_height;

	array = ft_split(data->map2, '\n');// haritayı çift poiner olarak alıyor. henüz parse edilmedi.
	i = -1;
	while (array[++i])
		if (check_max_number(array, ft_strlen_mod(array[i]), i) == 1)// strlen_mode satır uzunluklarını bulur. // en uzun satırı bulur.
			break ;
	map_width = ft_strlen_mod(array[i]); // en uzun satırın uzunluğu.
	i = -1;
	map_height = 0;
	while (data->map2[++i])
		if (data->map2[i] == '\n')
			map_height++;
	if (map_width < map_height)// hangisi büyükse büyük olan baz alınarak eşitlenir.
		map_width = map_height;
	else
		map_height = map_width;//!!!!!!!!!!!!!!!!!!!!!!!!!!!! NEDENNNNNNNNNNNNNN EŞİTLİİİİİİİİİYOOOOOOOOOORRRRRRRR !!!!!!!!!!!!!!
	data->map_size = map_height;// satır sayısı buranın içinde.
	free_char_array(array);
	setup_int_map2(data, map_width, map_height);// !!!!! INTEGER !!!!! data->map3 oluşturdu size ını burada belirlenen max width ve height yaptı ve içini 0 lar ile doldurdu.
	// oyuncunun konumu ve yönü int olarak map3 e atıldı ve artık biliniyor.
	return (check_map5(data));
}
