/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:24:04 by bdevessi          #+#    #+#             */
/*   Updated: 2019/04/12 17:12:37 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

int		main(int argc, char **argv)
{
	(void)argc, (void)argv;
	t_fdf		fdf;


	if (argc < 2 || !init_fdf(&fdf))
		return (1); //error
	t_input input = parse(argv[1]);
	for (size_t i = 0; i < input.len; i++) {
		printf("%f\n", input.vertices[i].z);
	}
	render(&fdf);
}
