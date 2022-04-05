/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:35:58 by esormune          #+#    #+#             */
/*   Updated: 2022/03/29 23:38:22 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Generates name for the image based on time.
*/
void	bmp_name(char *str)
{
	char	*timestr;
	time_t	t;

	ft_bzero(str, 100);
	time(&t);
	timestr = ft_itoa_size_t_base(t, 10);
	if (!timestr)
		return ;
	ft_strcpy(str, "screenshot");
	ft_strcat(str, timestr);
	ft_strcat(str, ".bmp");
	free(timestr);
}

/*
** Creates the file header required for a bmp file. The fields are
** a signature ("BM" for bitmap), file size (4 bytes), and start of
** pixel array, denoted by adding the headers together. The rest of
** the fields are set to a default 0.
*/
static unsigned char	*create_bmp_file_header(int height, int width)
{
	int				file_size;
	unsigned char	*file_header;

	file_header = ft_calloc(FILE_HEADER_SIZE, sizeof(unsigned char));
	if (!file_header)
		ft_getout("Malloc failure.");
	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE \
		+ BYTES_PER_PIXEL * height * width;
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
	return (file_header);
}

/*
** Creates the info header required for a bmp file. The fields are
** header size, image width (4 bytes), height width (4 bytes),
** number of colour planes, and bits per pixel (24). The rest of the fields
** are set to a default 0.
*/
static unsigned char	*create_bmp_info_header(int height, int width)
{
	unsigned char	*info_header;

	info_header = ft_calloc(INFO_HEADER_SIZE, sizeof(unsigned char));
	if (!info_header)
		ft_getout("Malloc failure.");
	info_header[0] = (unsigned char)(INFO_HEADER_SIZE);
	info_header[4] = (unsigned char)(width);
	info_header[5] = (unsigned char)(width >> 8);
	info_header[6] = (unsigned char)(width >> 16);
	info_header[7] = (unsigned char)(width >> 24);
	info_header[8] = (unsigned char)(height);
	info_header[9] = (unsigned char)(height >> 8);
	info_header[10] = (unsigned char)(height >> 16);
	info_header[11] = (unsigned char)(height >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(BYTES_PER_PIXEL * 8);
	return (info_header);
}

/*
** Creates the bitmap from given unsigned char array. The file
** requires a file header and an image header, as well as padding.
** These are default values for a 3bpp rgb bitmap. The dimensions
** will follow the size of the window. Writes one line at a time
** with the appropriate padding.
*/
void	create_bmp(unsigned char *image, char *file_name)
{
	t_bmp			bmp;
	unsigned char	*padding;
	int				i;
	FILE			*file;

	bmp.f_head = create_bmp_file_header(WIN_H, WIN_W);
	bmp.i_head = create_bmp_info_header(WIN_H, WIN_W);
	bmp.padding_size = (4 - (WIN_W * BYTES_PER_PIXEL) % 4) % 4;
	padding = ft_calloc(3, sizeof(unsigned char));
	if (!padding)
		ft_getout("Malloc error.");
	file = fopen(file_name, "wb");
	fwrite(bmp.f_head, 1, FILE_HEADER_SIZE, file);
	fwrite(bmp.i_head, 1, INFO_HEADER_SIZE, file);
	i = WIN_H - 1;
	while (i >= 0)
	{
		fwrite(image + ((i--) * WIN_W * BYTES_PER_PIXEL),
			BYTES_PER_PIXEL, WIN_W, file);
		fwrite(padding, 1, bmp.padding_size, file);
	}
	fclose(file);
	free(bmp.f_head);
	free(bmp.i_head);
	free(padding);
}
