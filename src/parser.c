/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 19:27:14 by bdevessi          #+#    #+#             */
/*   Updated: 2019/04/12 17:27:18 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>

#include "fdf.h"
#include "libft.h"

bool	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ');
}

t_input	parse(const char *filename)
{
	const int	fd = open(filename, O_RDONLY);
	t_input		*input;
	t_reader	reader;
	int		altitude;
	char		c;
	int		sign;
	bool		reset;
	t_unit		*coords;

	if (fd == -1)
	{
		perror("fdf: ");
		return ((t_input) {
			.cap = 0
		});
	}
	reader_init(&reader);
	input = NULL;
	altitude = 0;
	sign = 1;
	reset = true;
	coords = (t_unit[2]) { 0, 0 };
	while (get_char(&reader, fd, &c, 1) > 0)
	{
		ft_putf("char = %c\n", c);
		if (!(ft_isdigit(c) || c == '-' || ft_isspace(c)))
			return ((t_input) {
				.cap = 0
			}); //error
		if (c == '-')
			sign = -1;
		else if (ft_isdigit(c))
		{
			reset = true;
			altitude = altitude * 10 + (c - '0');
		}
		else
		{
			if (reset)
			{
				printf("sign = %d\n", sign);
				input = input_push(input, (t_vtx3d) {
					.x = coords[0]++,
					.y = coords[1],
					.z = (t_unit)(sign * altitude)
				});
				printf("altitude = %f\n", (t_unit)(sign * altitude));
				reset = false;
			}
			else if (c == '\n')
				coords[1]++;
			altitude = 0;
			sign = 1;
		}
	}
	return (*input_push(input, (t_vtx3d) {
		.x = coords[0]++,
		.y = coords[1],
		.z = altitude
	}));
}
