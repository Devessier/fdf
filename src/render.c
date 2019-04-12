/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:26:27 by bdevessi          #+#    #+#             */
/*   Updated: 2019/04/12 12:09:53 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <mlx.h>
#include <stdbool.h>
#include <stdlib.h>

const int		g_window_height = 800;
const int		g_window_width = 1000;
const int		g_canvas_height = 700;
const int		g_canvas_width = 1000;
const char		*g_window_title = "FDF";
static const int	g_canvas_background = 0xE1E2E1;

bool			init_fdf(t_fdf *fdf)
{
	void	*mlx;
	void	*window;
	void	*image;
	int	bits_per_pixel;
	int	size_line;
	int	endian;
	
	if ((mlx = mlx_init()) != NULL)
		if ((window = mlx_new_window(mlx, g_window_width,
			g_window_height, (char *)g_window_title)) != NULL)
			if ((image = mlx_new_image(mlx, g_canvas_width, g_canvas_height)) != NULL)
			{
				fdf->__mlx = mlx;
				fdf->__window = window;
				fdf->__image = image;
				fdf->__buffer = (t_buffer)mlx_get_data_addr(image, &bits_per_pixel, &size_line, &endian);
				fdf->space_around_plots = 20;
				return (true);
			}
	return (false);
}

static void		paint_background(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < g_canvas_width * g_canvas_height)
		fdf->__buffer[i++] = g_canvas_background;
}

int			render(t_fdf *fdf)
{
	header(fdf);
	paint_background(fdf);
	draw_line(fdf, (t_vtx2d) { 10., 50., 1. }, (t_vtx2d) { 500., 75., 1. });
	mlx_put_image_to_window(fdf->__mlx, fdf->__window, fdf->__image, 0, g_header_height);
	mlx_loop(fdf->__mlx);
	return 0;
}
