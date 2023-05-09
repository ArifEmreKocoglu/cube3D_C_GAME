/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:48:02 by eayyildi          #+#    #+#             */
/*   Updated: 2023/05/03 11:28:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_map3(t_data *data)
{
	int	i;
	int	found;

	i = -1;
	found = 0;
	while (data->map2[++i])
	{
		if (data->map2[i] == 'N' || data->map2[i] == 'W' \
		|| data->map2[i] == 'E' || data->map2[i] == 'S')
		{
			found = 1;// OYUNCUYU buldu. 
			break ;
		}
	}
	if (found != 1)
		return (print_error("There is no player in map.\n"));
	i++;
	while (data->map2[++i])
	{
		if (data->map2[i] == 'N' || data->map2[i] == 'W' \
		|| data->map2[i] == 'E' || data->map2[i] == 'S')
			return (print_error("There must be only one player in the map\n"));
		i++;
	}
	return (check_map4(data));
}

int	check_map2(t_data *data)
{
	int		i;

	i = 0;
	while (data->map2[i])
	{
		if (data->map2[i] != '1' && data->map2[i] != '0' \
		&& data->map2[i] != '\t' && data->map2[i] != ' ' \
		&& data->map2[i] != '\n' && data->map2[i] != 'N' \
		&& data->map2[i] != 'W' && data->map2[i] != 'E' \
		&& data->map2[i] != 'S')
			return (print_error("Invalid character in map.\n"));
		i++;
	}
	return (check_map3(data));// check_map3 oyuncu yoksa veya birden fazla varsa hata döndürür.
}

char	*get_data_value(t_data *data, int index, int mode)
{
	int		i;
	int		temp;
	char	*array;

	i = 0;
	if (mode == 1)
		while (data->map[index] == '\t' || data->map[index] == ' ' \
		|| data->map[index] == '\n')
			index++;
	else
		while (data->map[index] == '\n')
			index++;
	temp = index - 1;
	if (mode == 1)
		while (data->map[++temp] != '\n' && data->map[temp] != ' ' \
		&& data->map[temp] != '\t')
			i++;
	else
		while (data->map[++temp] != '\0')
			i++;
	array = ft_substr(data->map, index, i);
	return (array);
}

void	setup_imgs(t_data *data, int index, int data_key_code)
{
	if (data_key_code == 1)
		data->imgs[0] = get_data_value(data, index, 1);
	else if (data_key_code == 2)
		data->imgs[1] = get_data_value(data, index, 1);
	else if (data_key_code == 3)
		data->imgs[2] = get_data_value(data, index, 1);
	else if (data_key_code == 4)
		data->imgs[3] = get_data_value(data, index, 1);
	else if (data_key_code == 5)
		data->imgs[4] = get_data_value(data, index, 1);
	else if (data_key_code == 6)
		data->imgs[5] = get_data_value(data, index, 1);
}

int	check_double_data(t_data *data, int data_key_code)
{
	if (data_key_code == 1 && data->no_bool != 1)
		data->no_bool = 1;
	else if (data_key_code == 2 && data->so_bool != 1)
		data->so_bool = 1;
	else if (data_key_code == 3 && data->we_bool != 1)
		data->we_bool = 1;
	else if (data_key_code == 4 && data->ea_bool != 1)
		data->ea_bool = 1;
	else if (data_key_code == 5 && data->f_bool != 1)
		data->f_bool = 1;
	else if (data_key_code == 6 && data->c_bool != 1)
		data->c_bool = 1;
	else
		return (-1);
	return (0);
}
