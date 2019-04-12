/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 19:28:28 by bdevessi          #+#    #+#             */
/*   Updated: 2019/04/12 16:35:21 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_F
# define FDF_F
# include <stdint.h>
# include <stdbool.h>
# include <sys/types.h>
# define ALTITUDE_MAX 2147483647
# define ALTITUDE_MIN -2147483648
# define ALTITUDE_MAX_LEN 11

typedef uint32_t	*t_buffer;
typedef void		*t_view;
typedef float		t_unit;
typedef struct s_vtx3d	*t_map;

/*
** Vertex
*/

typedef struct		s_vtx2d
{
	t_unit	x;
	t_unit	y;
	t_unit	w;
}			t_vtx2d;

typedef struct		s_vtx3d
{
	t_unit	x;
	t_unit	y;
	t_unit	z;
	t_unit	w;
}			t_vtx3d;

t_vtx2d			mk_vtx2d(t_unit x, t_unit y);
t_vtx3d			mk_vtx3d(t_unit x, t_unit y, t_unit z);

/*
** Vector
*/

typedef struct		s_vec3d
{
	t_unit	x;
	t_unit	y;
	t_unit	z;
	t_unit	w;
}			t_vec3d;

t_vec3d			mk_vec3d(t_unit x, t_unit y, t_unit z);

/*
** FDF
*/

typedef struct		s_fdf
{
	void		*__mlx;
	void		*__window;
	t_view		__image;
	t_buffer	__buffer;
	t_map		map;

	t_unit		space_around_plots;
	size_t		map_len;
	size_t		plots_per_line;
}			t_fdf;

/*
** Array functions
*/

typedef struct		s_input
{
	size_t		len;
	size_t		cap;
	struct s_vtx3d	vertices[];
}			t_input;

/**
** Reader
*/

typedef struct		s_reader
{
	char	buffer[4096];
	size_t	index;
	size_t	len;
}			t_reader;

void			reader_init(t_reader *this);
ssize_t			get_char(t_reader *this, const int fd, char *tab, size_t size);
t_input			*input_push(t_input *input, struct s_vtx3d vtx);

/*
** Parser
*/

t_input			parse(const char *filename);

/*
** Drawing functions
*/

void		draw_line(t_fdf *fdf, t_vtx2d a, t_vtx2d b);

/*
** FDF Initialization
*/

bool			init_fdf(t_fdf *fdf);

/*
** Reader
*/

t_vtx3d			*reader(void);

/*
** Render process
*/

void			header(t_fdf *fdf);
int			render(t_fdf *fdf);

/*
** Program globals
*/

extern const int	g_window_height;
extern const int	g_window_width;

extern const int	g_canvas_height;
extern const int	g_canvas_width;

extern const int	g_header_height;

extern const char	*g_window_title;

#endif
