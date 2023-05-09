/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:48:05 by eayyildi          #+#    #+#             */
/*   Updated: 2023/05/03 11:29:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_digit(char *array)
{
	int		i;

	i = -1;
	while (array[++i])
		if (!ft_isdigit(array[i]))
			return (1);
	return (0);
}

int	check_f_c(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	if (i != 3)
		return (print_error("Invalid rgb color code.\n"));
	i = -1;
	while (array[++i])
		if (check_digit(array[i]))
			return (print_error("Invalid rgb color code.\n"));
	i = -1;
	while (array[++i])
		if (!(ft_atoi(array[i]) >= 0 && ft_atoi(array[i]) <= 255))
			return (print_error("Invalid rgb color code.\n"));
	return (0);
}

int	setup_f_c(t_data *data)
{
	int		i;
	char	**array_f;
	char	**array_c;

	array_f = ft_split(data->imgs[4], ',');
	array_c = ft_split(data->imgs[5], ',');
	if (check_f_c(array_c) || check_f_c(array_f))
	{
		free_char_array(array_c);
		free_char_array(array_f);
		return (1);
	}
	data->f_rgb = (int *)malloc(sizeof(int) * 3);
	data->c_rgb = (int *)malloc(sizeof(int) * 3);
	i = -1;
	while (++i < 3)
	{
		data->f_rgb[i] = ft_atoi(array_f[i]);
		data->c_rgb[i] = ft_atoi(array_c[i]);
	}
	free_char_array(array_c);
	free_char_array(array_f);
	return (setup_int_map(data));
}

int	check_map4(t_data *data)
{
	int	i;

	i = 0;
	while (data->map2[i])
	{
		if (data->map2[i] == '\n' && (data->map2[i + 1] != '1' \
		&& data->map2[i + 1] != '\t' && data->map2[i + 1] != ' '))// satır başlangıcı bu karakterler harici hiçbir şey olamaz.
			return (print_error \
			("There is new line between the lines on map.\n"));
		else if ((data->map2[i] == '\t' || data->map2[i] == ' ') \
		&& (data->map2[i + 1] == '\n'))// satır sonunda boşluk veya tab olamaz.
			return (print_error \
			("There is new line between the lines on map.\n"));
		i++;
	}
	return (setup_f_c(data));// rgb renk kodlarını integer yaparak structa kaydeder.
}

