/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:48:40 by eayyildi          #+#    #+#             */
/*   Updated: 2023/05/03 11:26:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_data	data;

	fd = open(argv[1], O_RDONLY);
	if (argc != 2 || fd < 3 || check_arg(argv[1])) // map dosyası uzantı kontrolü.
		return (print_error("Something wrong with arguments.\n"));
	if (before_start_game(fd, &data)) // // dizi doldurma işlemi yapar, haritayı atar.
		return (ft_free_map(&data));
	if (start_game(&data))
		return (ft_free_map(&data));
	return (0);
}
