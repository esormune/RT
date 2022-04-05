/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_defs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:46:05 by esormune          #+#    #+#             */
/*   Updated: 2022/04/05 20:46:07 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEFS_H
# define FT_DEFS_H

# include <stdlib.h>

# define TRUE	1
# define FALSE	0

//buffer size for get_next_line
# define BUFF_SIZE 32

//for ft_noise
# define NOISE_SEED 0

typedef int	t_bool;

typedef struct s_matrix
{
	double	m[4][4];
}			t_matrix;

typedef struct s_pixel
{
	uint32_t	x;
	uint32_t	y;
}				t_pixel;

typedef struct s_vec4
{
	double	x;
	double	y;
	double	z;
	double	w;
}			t_vec4;

typedef struct s_hsl
{
	double	h;
	double	s;
	double	l;
}			t_hsl;

typedef struct s_colour
{
	double		r;
	double		g;
	double		b;
	double		a;
}				t_colour;
typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}			t_vec;

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct s_complex
{
	float	x;
	float	y;
}			t_complex;

#endif
