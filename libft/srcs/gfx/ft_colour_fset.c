/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colour_fset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:52:48 by esormune          #+#    #+#             */
/*   Updated: 2022/03/10 16:03:19 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Sets a colour struct with rgb values. Expects floats for values.
*/
void	ft_colour_fset(t_colour *c, double r, double g, double b)
{
	c->r = r;
	c->g = g;
	c->b = b;
	c->a = 0.0;
}
