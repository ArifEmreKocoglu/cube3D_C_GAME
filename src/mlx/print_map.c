/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocoglu <akocoglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:48:25 by eayyildi          #+#    #+#             */
/*   Updated: 2023/05/09 15:30:23 by akocoglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_map5(t_data *data, int x)
{
	int		y;
	int		color;

	y = data->draw_start;
	while (y < data->draw_end)
	{
		data->tex_y = (int)data->tex_pos & (IMG_HEIGHT - 1);
		data->tex_pos += data->step;
		color = 0;
		if (data->raydir_y < 0 && data->side == 1)
			color = data->imgs_data[1][IMG_HEIGHT \
				* data->tex_y + data->tex_x];
		else if (data->raydir_x < 0 && data->side == 0)
			color = data->imgs_data[2][IMG_HEIGHT \
				* data->tex_y + data->tex_x];
		else if (data->raydir_y > 0 && data->side == 1)
			color = data->imgs_data[0][IMG_HEIGHT \
				* data->tex_y + data->tex_x];
		else if (data->raydir_x > 0 && data->side == 0)
			color = data->imgs_data[3][IMG_HEIGHT \
				* data->tex_y + data->tex_x];
		data->screen_img_data[y * WIN_WIDTH + x] = color;
		y++;
	}
}

void	print_map4(t_data *data)
{
	data->line_height = (int)(WIN_HEIGHT / data->perp_wall_dist); // basılacak resmin yüksekliği 
	data->draw_start = -data->line_height / 2 + WIN_HEIGHT / 2; // geçerli şeriti doldurmak için en düşük ve en yüksek pixeli hesapla
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + WIN_HEIGHT / 2;
	if (data->draw_end >= WIN_HEIGHT)
		data->draw_end = WIN_HEIGHT - 1;
	if (data->side == 0)
		data->wall_x = data->pos_y + data->perp_wall_dist \
			* data->raydir_y;
	else
		data->wall_x = data->pos_x + data->perp_wall_dist \
			* data->raydir_x;
	data->wall_x -= floor(data->wall_x);
	data->tex_x = (int)(data->wall_x * (double)IMG_WIDTH);
	if (data->side == 0 && data->raydir_x > 0)
		data->tex_x = IMG_WIDTH - data->tex_x - 1;
	if (data->side == 1 && data->raydir_y < 0)
		data->tex_x = IMG_WIDTH - data->tex_x - 1;
	data->step = 1.0 * IMG_HEIGHT / data->line_height;
	data->tex_pos = (data->draw_start - WIN_HEIGHT / 2 \
		+ data->line_height / 2) * data->step;
}

void	print_map3(t_data *data)
{
	while (data->hit == 0) // duvara çarpmadıysa
	{
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_dist_x; // duvara çarpmadığı sürece ışının geçtiği yerleri topluyoruz.
			data->map_x += data->step_x; // duvara çarpmadıkça ışının konumunu ekliyoruz.(ışının ilerlediği yöne göre "+" "-")
			data->side = 0; // ışın x taraflı duvara çarptı.
		}
		else
		{
			data->side_dist_y += data->delta_dist_y;
			data->map_y += data->step_y;
			data->side = 1; // ışın y taraflı duvara çarptı.
		}
		if (data->map3[data->map_x][data->map_y] == 1) // bulunduğu yer duvar ise 1 yap çık.
			data->hit = 1;
	}
	if (data->side == 0)
		data->perp_wall_dist = (data->map_x - data->pos_x \   
			+ (1 - data->step_x) / 2) / data->raydir_x;   // x için ;burada duvar ile oyuncu arasındaki dik uzunluğu hesaplıyor.
	else
		data->perp_wall_dist = (data->map_y - data->pos_y \
			+ (1 - data->step_y) / 2) / data->raydir_y;  // y için ;burada duvar ile oyuncu arasındaki dik uzunluğu hesaplıyor.
}

void	print_map2(t_data *data)
{
	if (data->raydir_x < 0) // ışın negatif yönde ilerliyor.
	{
		data->step_x = -1; // ışın negatif yönde.
		data->side_dist_x = (data->pos_x \
			- data->map_x) * data->delta_dist_x; // (data->side_dist_x) ışının x gördüğünde çarptığı ilk nokta.
	}
	else
	{
		data->step_x = 1;
		data->side_dist_x = (data->map_x + 1.0 \
			- data->pos_x) * data->delta_dist_x;
	}
	if (data->raydir_y < 0)
	{
		data->step_y = -1;
		data->side_dist_y = (data->pos_y \
			- data->map_y) * data->delta_dist_y;
	}
	else
	{
		data->step_y = 1;
		data->side_dist_y = (data->map_y + 1.0 \
			- data->pos_y) * data->delta_dist_y;
	}
}

int print_map(t_data *data)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		set_data_rc(data, x);
		print_map2(data);
		print_map3(data);
		print_map4(data);
		print_map5(data, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
		data->screen_img, 0, 0);
		//Resimlerı ekrana basmamıza yarar. Parametre olarak mlx_ptr, win_ptr, img_ptr ve resmin pencerenin hangi konuma basılacagını belirtmek için
		//bir x y kordınatı alır örnek olarak : (0, 0) noktası verelim
	return (0);
}
