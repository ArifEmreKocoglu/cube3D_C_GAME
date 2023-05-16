/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocoglu <akocoglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:48:22 by eayyildi          #+#    #+#             */
/*   Updated: 2023/05/09 17:27:41 by akocoglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_data_rc(t_data *data, int x)
{
	double	camera_x;// Kameranın X koordinatı

	camera_x = 2 * x / (double)WIN_WIDTH -1; // Kameranın yatay eksende -1 ile 1 arasında değerini temsil eder.
	//printf("****************************************************************\n");
	//printf("CAMERAX=%f\n", camera_x);
	data->raydir_x = data->dir_x + data->plane_x * camera_x;// dir_x : kameranın x yönündeki yönü
	//printf("raydir_x=%f\n", data->raydir_x);
	data->raydir_y = data->dir_y + data->plane_y * camera_x;
	//printf("raydir_y=%f\n", data->raydir_y);
	data->map_x = (int)data->pos_x;
	//printf("map_x=%d\n", data->map_x);
	data->map_y = (int)data->pos_y;
	//printf("map_y=%d\n", data->map_y);
	//printf("****************************************************************\n");
	data->delta_dist_x = fabs(1 / data->raydir_x); // ışının x noktasından diğer x noktsına bir birim mesafesi
	data->delta_dist_y = fabs(1 / data->raydir_y); // ışının y noktasından diğer y noktsına bir birim mesafesi
	data->hit = 0; // ışının nesnelere çarpıp çarpmaması tespit edilir.
}

void	key_press_helper3(t_data *data, int key)
{
	if (key == RIGHT)
	{
		if (data->map3[(int)data->pos_x][(int)(data->pos_y \
			- (data->dir_x * data->move_speed))] != 1)
			data->pos_y -= data->dir_x * data->move_speed;
		printf("POS_Y_RIGHT=%f\n", data->pos_y);
		printf("DİR_Y_RIGHT=%f\n", data->dir_y);
		if (data->map3[(int)(data->pos_x + (data->dir_y \
			* data->move_speed))][(int)data->pos_y] != 1)
			data->pos_x += data->dir_y * data->move_speed;
		printf("POS_X_RIGHT=%f\n", data->pos_x);
		printf("DİR_X_RIGHT=%f\n", data->dir_x);
	}
	if (key == LEFT)
	{
		if (data->map3[(int)(data->pos_x)][(int)(data->pos_y \
			+ (data->dir_x * data->move_speed))] != 1)
			data->pos_y += data->dir_x * data->move_speed;
		printf("POS_Y_LEFT=%f\n", data->pos_y);
		printf("DİR_Y_LEFT=%f\n", data->dir_y);
		if (data->map3[(int)(data->pos_x - (data->dir_y \
			* data->move_speed))][(int)(data->pos_y)] != 1)
			data->pos_x -= data->dir_y * data->move_speed;
		printf("POS_X_LEFT=%f\n", data->pos_x);
		printf("DİR_X_LEFT=%f\n", data->dir_x);
	}
}

void	key_press_helper2(t_data *data, int key)
{
	double	olddir_x;
	double	oldplane_x;

	if (key == UP)
	{
		if (data->map3[(int)(data->pos_x + data->dir_x \
			* data->move_speed)][(int)(data->pos_y)] != 1)
			data->pos_x += data->dir_x * data->move_speed;
		printf("POS_X_UP=%f\n", data->pos_x);
		printf("DİR_X_UP=%f\n", data->dir_x);
		if (data->map3[(int)(data->pos_x)][(int)(data->pos_y \
			+ data->dir_y * data->move_speed)] != 1)
			data->pos_y += data->dir_y * data->move_speed;
		printf("POS_Y_UP=%f\n", data->pos_y);
		printf("DİR_Y_UP=%f\n", data->dir_y);
	}
	if (key == CAMERA_RIGHT)
	{
		olddir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(-data->rot_speed) \
			- data->dir_y * sin(-data->rot_speed);
		printf("DİR_X_CAMRIGHT=%f\n", data->dir_x);
		data->dir_y = olddir_x * sin(-data->rot_speed) \
			+ data->dir_y * cos(-data->rot_speed);
		printf("DİR_Y_CAMRIGHT=%f\n", data->dir_y);
		oldplane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(-data->rot_speed) \
			- data->plane_y * sin(-data->rot_speed);
		printf("plane_X_CAMERERIGHT=%f\n", data->plane_x);
		data->plane_y = oldplane_x * sin(-data->rot_speed) \
			+ data->plane_y * cos(-data->rot_speed);
		printf("plane_Y_CAMERALEFT=%f\n", data->plane_y);
	}
}

void	key_press_helper(t_data *data, int key)
{
	double	olddir_x;
	double	oldplane_x;

	if (key == BACK)
	{
		if (data->map3[(int)(data->pos_x - data->dir_x \
			* data->move_speed)][(int)(data->pos_y)] != 1)
			data->pos_x -= data->dir_x * data->move_speed;
		printf("POS_X_UP=%f\n", data->pos_x);
		printf("DİR_X_UP=%f\n", data->dir_x);
		if (data->map3[(int)(data->pos_x)][(int)(data->pos_y \
			- data->dir_y * data->move_speed)] != 1)
			data->pos_y -= data->dir_y * data->move_speed;
		printf("POS_Y_UP=%f\n", data->pos_y);
		printf("DİR_Y_UP=%f\n", data->dir_y);
	}
	if (key == CAMERA_LEFT)
	{
		olddir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(data->rot_speed) \
			- data->dir_y * sin(data->rot_speed);
		printf("DİR_X_CAMLEFT=%f\n", data->dir_x);
		data->dir_y = olddir_x * sin(data->rot_speed) \
			+ data->dir_y * cos(data->rot_speed);
		printf("DİR_Y_CAMLEFT=%f\n", data->dir_y);
		oldplane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(data->rot_speed) \
			- data->plane_y * sin(data->rot_speed);
		printf("plane_X_CAMERALEFT=%f\n", data->plane_x);
		data->plane_y = oldplane_x * sin(data->rot_speed) \
			+ data->plane_y * cos(data->rot_speed);
		printf("plane_Y_CAMERALEFT=%f\n", data->plane_y);
	}
}
