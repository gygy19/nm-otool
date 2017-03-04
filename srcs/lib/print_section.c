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

static void	finish_line(int currentlength)
{
	while (currentlength < 16)
	{
		ft_printf("   ");
		currentlength++;
	}
}

void	print_section_text(struct section_64 *section, void *header,\
		int flags)
{
	char	*content;
	size_t	i;
	size_t	tmp;

	ft_printf("Contents of (__TEXT,__text) section\n");
	content = getptr_section(section, header);
	i = 0;
	while (i < section->size)
	{
		ft_printf("%08d", CASTHEADER_X32->filetype - 1);
		print_addr(section->addr + i);
		ft_printf("\t");
		tmp = i;
		print_32bits(content, section->size, &i);
		if (flags & flag_a)
		{
			finish_line(i - tmp);
			ft_printf("\t");
			print_ascii_32bits(content, section->size, tmp);
		}
		ft_printf("\n");
	}
}
