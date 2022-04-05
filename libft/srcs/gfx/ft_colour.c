/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:43:28 by esormune          #+#    #+#             */
/*   Updated: 2022/03/10 15:57:27 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Converts integer rgb values into a uint32_t colour.
*/
int	ft_colour(int r, int g, int b)
{
	return ((r * 65536) + (g * 256) + b);
}
