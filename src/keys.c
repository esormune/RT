/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:00 by esormune          #+#    #+#             */
/*   Updated: 2022/03/29 16:38:27 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Handles key events.
*/
void	e_keys(SDL_Event e, t_img *img)
{
	int	key;

	key = e.key.keysym.sym;
	if (key == SDLK_ESCAPE)
		img->run = FALSE;
	else if (key == SDLK_s)
		screenshot_image(img);
}
