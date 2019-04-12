/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 19:28:48 by bdevessi          #+#    #+#             */
/*   Updated: 2019/04/12 16:57:57 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "fdf.h"
#include "libft.h"

t_input	*input_push(t_input *input, t_vtx3d vtx)
{
	t_input	*tmp;
	size_t	cap;
	size_t	i;

	if (!input || !(input->len < input->cap))
	{
		cap = input == NULL ? 2 : (input->cap + !input->cap) << 1;
		if (!(tmp = malloc(sizeof(t_input) + sizeof(t_vtx3d) * cap)))
			return (NULL);
		i = 0;
		while (input != NULL && i++ < input->len)
			tmp->vertices[i - 1] = input->vertices[i - 1];
		free(input);
		tmp->vertices[i] = vtx;
		tmp->len = i + input == NULL;
		tmp->cap = cap;
		return (tmp);
	}
	input->vertices[input->len++] = vtx;
	return (input);
}

void	reader_init(t_reader *this)
{
	*this = (t_reader) {
		.len = 0,
		.index = 0
	};
}

ssize_t	get_char(t_reader *this, const int fd, char *tab, size_t size)
{
	size_t	remaining;
	size_t	to_copy;
	size_t	copied;

	remaining = this->len - this->index;
	if (remaining < size)
	{
		copied = remaining;
		ft_memmove(tab, this->buffer + this->index, remaining);
		size -= remaining;
		this->len = read(fd, this->buffer, 4096);
		this->index = 0;
		remaining = this->len;
	}
	else
		copied = 0;
	to_copy = remaining < size ? remaining : size;
	ft_memcpy(tab, this->buffer + this->index, to_copy);
	this->index += to_copy;
	return (to_copy + copied);
}
