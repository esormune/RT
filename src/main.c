/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:10 by esormune          #+#    #+#             */
/*   Updated: 2022/03/30 21:41:23 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	image_cleanup(t_img *img)
{
	int	i;

	i = 0;
	while (i < img->scene.imgcount)
	{
		if (img->scene.imgs[i].loaded || img->scene.imgs[i].incorrect_bpp)
			SDL_FreeSurface(img->scene.imgs[i].surface);
		i++;
	}
	free(img->scene.imgs);
}

void	cleanup(t_img *img)
{
	int	i;

	i = 0;
	free(img->win_buffer->px);
	free(img->win_buffer);
	free(img->channels->r);
	free(img->channels->g);
	free(img->channels->b);
	free(img->channels);
	free(img->scene.objs);
	free(img->scene.lights);
	if (img->scene.imgs)
		image_cleanup(img);
	SDL_DestroyTexture(img->win_tex);
	SDL_DestroyRenderer(img->rend);
	SDL_DestroyWindow(img->win);
	SDL_Quit();
}

void	loop(t_img *img)
{
	SDL_Event	e;

	if (SDL_WaitEvent(&e))
	{
		if (e.type == SDL_QUIT)
			img->run = FALSE;
		if (e.type == SDL_WINDOWEVENT && \
			e.window.event == SDL_WINDOWEVENT_CLOSE)
			img->run = FALSE;
		if (e.type == SDL_WINDOWEVENT && \
			e.window.event == SDL_WINDOWEVENT_EXPOSED)
			draw_img_to_window(img);
		if (e.type == SDL_KEYDOWN)
			e_keys(e, img);
	}
}

int	main(int argc, char **argv)
{
	t_img	img;

	if (argc == 2)
	{
		ft_bzero(&img, sizeof(t_img));
		parser(&img.scene, argv[1]);
		init(&img);
		render(&img);
		while (img.run)
			loop(&img);
		cleanup(&img);
	}
	else
		ft_printf("Usage: ./RT [scene]\n");
	return (0);
}
