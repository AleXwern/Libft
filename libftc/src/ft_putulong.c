/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putulong.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 22:40:40 by AleXwern          #+#    #+#             */
/*   Updated: 2022/06/19 22:58:09 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putulong(t_uint64 n)
{
	unsigned char	c;

	if (n > 9)
		ft_putulong(n / 10);
	c = (n % 10) + 48;
	write(1, &c, 1);
}
