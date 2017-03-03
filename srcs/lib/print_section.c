/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_section.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:47:47 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/03 10:47:48 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	print_ascii_32bits(char *ptr, int size, int o)
{
	int i;

	i = 0;
	while (o < size && i < 16)
	{
		if (ptr[o] > 33 && ptr[o] < 127)
			ft_putchar(ptr[o]);
		else
			ft_putchar('.');
		i++;
		o++;
	}
}

void	print_section_text(struct section_64 *section, void *header)
{
	char	*content;
	size_t	i;
	size_t	tmp;

	ft_printf("Contents of (__TEXT,__text) section\n");
	content = getptr_section(section, header);
	i = 0;
	while (i < section->size)
	{
		print_addr(section->addr + i);
		ft_printf("\t");
		tmp = i;
		print_32bits(content, section->size, &i);
		ft_printf(" ");
		print_ascii_32bits(content, section->size, tmp);
		ft_printf("\n");
	}
}
