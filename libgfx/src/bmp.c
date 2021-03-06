/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 12:16:01 by anystrom          #+#    #+#             */
/*   Updated: 2022/06/12 00:12:37 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

int			read_to_pixdata(t_bmphead bmp, uint32_t bread, int fd)
{
	int		toread;
	char	dummy[2000];

	while (bread < bmp.pdoff)
	{
		toread = bmp.pdoff - bread;
		if (toread > 2000)
			toread = 2000;
		read(fd, dummy, toread);
		bread += toread;
		if (toread == 0)
			return (0);
	}
	if (bread > bmp.pdoff)
		return (0);
	return (1);
}

uint32_t	*flip_arr(t_gfx gfx, char *corr)
{
	int		y;
	char	*dummy;

	y = gfx.hgt;
	if (!(dummy = (char*)ft_memalloc(gfx.wid * gfx.hgt * 4)))
		return (NULL);
	while (--y >= 0)
	{
		ft_memcpy(dummy + (gfx.hgt - y - 1) * (gfx.wid * 4),
			corr + (gfx.wid * y * 4), gfx.wid * 4);
	}
	free(corr);
	return ((uint32_t*)dummy);
}

char		*read_pixdata(char *corr, int fd, t_gfx gfx, int y)
{
	int		rd;
	char	exc[4];

	rd = 0;
	if (gfx.pitch % 4 != 0)
		rd += 4 - (gfx.pitch % 4);
	while (--y >= 0)
	{
		read(fd, corr + (gfx.pitch * y), gfx.pitch);
		if (rd > 0)
			read(fd, exc, rd);
	}
	return (corr);
}

uint32_t	*xbit_to_32(t_gfx gfx, int fd, int i, int b)
{
	char	*dummy;
	char	*corr;

	if (!(dummy = (char*)ft_memalloc(gfx.wid * gfx.hgt * 4)))
		return (NULL);
	if (!(corr = (char*)ft_memalloc(gfx.wid * gfx.hgt * (gfx.bpp / 8))))
		return (NULL);
	corr = read_pixdata(corr, fd, gfx, gfx.hgt);
	while (i < gfx.wid * gfx.hgt * (gfx.bpp / 8))
	{
		if (b % 4 >= (gfx.bpp / 8))
		{
			dummy[b] = 0xff;
			b++;
		}
		dummy[b] = corr[i];
		i++;
		b++;
	}
	free(corr);
	return ((uint32_t*)dummy);
}

t_gfx		read_bmp(char *file, int fd, int bread)
{
	t_bmphead	bmp;
	t_bmpinfo	head;
	t_gfx		gfx;

	ft_bzero(&gfx, sizeof(t_gfx));
	fd = open(file, O_RDONLY | O_BINARY);
	//free(file);
	if (fd == -1)
		return (gfx);
	bread = read(fd, &bmp, sizeof(bmp));
	if (bmp.bm != 0x4d42)
		return (gfx);
	bread += read(fd, &head, sizeof(head));
	if (!read_to_pixdata(bmp, bread, fd))
		return (gfx);
	gfx.wid = head.width;
	gfx.hgt = head.heigth;
	gfx.bpp = head.bpp;
	gfx.pitch = head.width * (gfx.bpp / 8);
	if (!(gfx.data = xbit_to_32(gfx, fd, 0, 0)))
		return (gfx);
	close(fd);
	return (gfx);
}
