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

void	print_section_text(struct section_64 *section, void *header)
{
	char	*content;
	size_t	i;
	ft_printf("Contents of (__TEXT,__text) section\n");

	content = getptr_section(section, header);
	i = 0;
	while (i < section->size)
	{
		print_addr(section->addr + i);
		ft_printf("\t");
		print_32bits(content, section->size, &i);
	}
}
