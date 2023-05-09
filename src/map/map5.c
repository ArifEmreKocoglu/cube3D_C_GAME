/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocoglu <akocoglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:48:14 by eayyildi          #+#    #+#             */
/*   Updated: 2023/05/09 18:10:19 by akocoglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_map5(t_data *data)
{
	int	i;
	int	j;
	int	br;
	int	**new_array;

	br = 0;
	new_array = copy_int_array(data->map3, data->map_size);// aynı diziyi tekrar int array olarak başka yere attık.
	i = -1;
	while (++i < data->map_size)
	{
		j = -1;
		while (++j < data->map_size)
		{
			if (new_array[i][j] >= 2)
				br = 1;// oyunucunun konumu bulmdu burada ve helpera gitti.
			if (br)
				break ;
		}
		if (br)
			break ;
	}
	if (check_map5_helper(new_array, data, i, j))// i ve j değeri OYUNCUNUN KONUMU, !!!!! OYUNCUNUN HAREKET EDEBİLME ALANINI KONTROL EDER, OYUNCU HAREKET EDEMEZ BİR POZİSYONDA İSE HATA DÖNDRÜR.
		return (1);
	return (0);
}

void	setup_player_helper(t_data *data, int number)
{
	if (number == 4)
	{
		data->plane_x = -0.66;
		data->dir_y = 1;
	}
	else if (number == 5)
	{
		data->plane_y = -0.66;
		data->dir_x = -1;
	}
}

int	setup_player(t_data *data, int x, int y, int number)
{
	data->pos_x = x + 0.5;// BAKILDI Bulduğumuz kutucuğun ortası
	data->pos_y = y + 0.5; // Bulunduğumuz kutucuğun ortası
	if (number == 2 || number == 4)
	{
		data->dir_x = 0;
		data->dir_y = -1;
		data->plane_x = 0.66;
		data->plane_y = 0;
		setup_player_helper(data, number);
	}
	else
	{
		data->dir_x = 1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = 0.66;
		setup_player_helper(data, number);
	}
	return (number);
}

void	int_map_helper(t_data *data, int i, int x, int y)
{
	int		number;

	if (data->map2[i] == 'N')
		number = setup_player(data, x, y, 2);// PARAMETREYE GÖRE DEĞER ATAMASI YAPAR POSITON gibi vb.. !!!BAKILACAKKK!!!
	else if (data->map2[i] == 'E')
		number = setup_player(data, x, y, 3);
	else if (data->map2[i] == 'S')
		number = setup_player(data, x, y, 4);
	else if (data->map2[i] == 'W')
		number = setup_player(data, x, y, 5);
	else
		number = data->map2[i] - '0';
	data->map3[x][y] = number;// data->map3 normalde 0 lar ile dolu oyuncunun konumuna göre bir int değeri alıyor.  oyuncunun konumu.
}
