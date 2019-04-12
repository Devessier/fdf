/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:05:19 by bdevessi          #+#    #+#             */
/*   Updated: 2019/04/12 12:03:00 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>

static const int	g_plot_color = 0x000000;

void	draw_line(t_fdf *fdf, t_vtx2d a, t_vtx2d b)
{
	const t_unit	delta_x = b.x - a.x;
	const t_unit	delta_y = b.y - a.y;
	const t_unit	delta_err = fabs(delta_y / delta_x);
	t_unit		error;
	int		y;
	int		x;

	error = .0;
	y = a.y;
	x = a.x;
	while (x < b.x)
	{
		fdf->__buffer[x++ + y * g_canvas_width] = g_plot_color;
		if ((error += delta_err) >= .5)
		{
			y += copysign(1.0, delta_y) * 1;
			error--;
		}
	}
}
