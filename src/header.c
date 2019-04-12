/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:26:06 by bdevessi          #+#    #+#             */
/*   Updated: 2019/04/12 11:59:48 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <mlx.h>

const int		g_header_height = 100;
static const int	g_header_background_color = 0x8FA3AD;
static const char	*g_header_text = "FDF - Baptou";
static const int	g_header_text_color = 0x000000;

void			header(t_fdf *fdf)
{
	const t_view	header_view = mlx_new_image(fdf->__mlx, g_window_width, g_header_height);
	t_buffer	header_buffer;
	int		i;
	int		lol;

	if (header_view == NULL
		|| (header_buffer = (t_buffer)mlx_get_data_addr(header_view, &lol, &lol, &lol)) == NULL)
		return ;
	i = 0;
	while (i < g_window_width * g_header_height)
		header_buffer[i++] = g_header_background_color;
	mlx_put_image_to_window(fdf->__mlx, fdf->__window, (t_view)header_view, 0, 0);
	mlx_string_put(fdf->__mlx, fdf->__window, (g_window_width - ft_strlen(g_header_text) * 10) / 2,
		g_header_height / 2 - 10 , g_header_text_color, (char *)g_header_text);
}
