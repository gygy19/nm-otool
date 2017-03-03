/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_32bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:47:34 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/03 10:47:36 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	print_32bits(char *ptr, size_t size, size_t *i)
{
	int	line;

	line = 0;
	while (line < 16 && *i < size)
	{
		print_hexa(ptr[*i] >> 4);
		print_hexa((char)(ptr[*i] - ((ptr[*i] >> 4) << 4)));
		ft_printf(" ");
		(*i)++;
		line++;
	}
	ft_printf("\n");
}
