/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 22:44:45 by AleXwern          #+#    #+#             */
/*   Updated: 2022/06/20 18:03:33 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"

void main(void)
{
	ft_putulongln(0xffffffffffffffff);
	ft_memcpy(malloc(10), "Yo hi 1234", 11);
	show_alloc_mem_ex();
}
