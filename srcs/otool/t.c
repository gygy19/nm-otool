/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:20:05 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/03 15:20:06 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void		ft_otool64(t_ofile *ofile)
{
	size_t	i;
	void	*ptr;

	ft_printf("Contents of (__TEXT,__text) section\n");
	load_section_text_64(ofile);
	if (ofile->section_text64 == NULL)
		return ;
	i = 0;
	ptr = ofile->map + ofile->swap(ofile, ofile->section_text64->offset);
	while (i < ofile->swap(ofile, ofile->section_text64->size))
	{
		ft_printf("%08d", ofile->swap(ofile, ofile->mh64->filetype) - 1);
		print_addr(ofile->swap(ofile, ofile->section_text64->addr) + i);
		ft_printf("\t");
		print_32bits(ptr, ofile->swap(ofile, ofile->section_text64->size), &i);
		ft_printf("\n");
	}
}

void		ft_otool32(t_ofile *ofile)
{
	size_t	i;
	void	*ptr;

	ft_printf("Contents of (__TEXT,__text) section\n");
	load_section_text_32(ofile);
	if (ofile->section_text == NULL)
		return ;
	i = 0;
	ptr = ofile->map + ofile->swap(ofile, ofile->section_text->offset);
	while (i < ofile->swap(ofile, ofile->section_text->size))
	{
		print_addr(ofile->swap(ofile, ofile->section_text->addr) + i);
		ft_printf("\t");
		print_32bits(ptr, ofile->swap(ofile, ofile->section_text->size), &i);
		ft_printf("\n");
	}
}
