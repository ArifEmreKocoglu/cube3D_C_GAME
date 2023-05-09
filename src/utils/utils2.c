/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:48:36 by eayyildi          #+#    #+#             */
/*   Updated: 2023/05/02 22:12:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_free_helper(t_data *data)
{
	free(data->f_rgb);
	free(data->c_rgb);
	free_int_array(data->map3, data->map_size);
}
//Kodun ayrıntılarına bakacak olursak, bu işlev basit bir işlem gerçekleştirir. İlk olarak, r, g ve b değerleri, 0x0ff (255) ile bit işlemi yaparak 8 bit (bir byte) aralığında sınırlandırılır. Bu, değerlerin 0-255 aralığında olduğunu garanti altına alır.

//Daha sonra, bu üç sınırlandırılmış değer, önce r 16 bit sola kaydırılarak (<<16), sonra g 8 bit sola kaydırılarak (<<8) ve en sonunda b ile birleştirilerek "veya" işlemi yapılır (|). Sonuçta, üç sayının birleşimi olan bir tamsayı (32 bit) elde edilir, bu da verilen RGB renk kodunu temsil eder.
int	rbg_to_int(int r, int g, int b) // Bu kod parçası, verilen üç tam sayı değeri (r, g ve b) ile temsil edilen bir RGB renk kodunu hesaplamak için kullanılır.
{
	return (((r & 0x0ff) << 16) | ((g & 0x0ff) << 8) | (b & 0x0ff));
}

void	ft_exit(t_data *data)
{
	ft_free_helper(data);
	ft_free_map(data);
	exit(EXIT_SUCCESS);
}
