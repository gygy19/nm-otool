/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 21:41:49 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/12 21:41:51 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include "asm_i386.h"

static void	print_sasm_64(t_ofile *ofile)
{
	if (ofile->sasm != NULL)
	{
		ft_printf("%08d", ofile->swap(ofile, ofile->mh64->filetype) - 1);
		print_addr(ofile->swap(ofile,\
			ofile->section_text64->addr) + ofile->length);
		ft_printf("\tasmtab[%2d][%2d] byte(%3d)",\
			ofile->opcode1, ofile->opcode2, ofile->byte);
		ft_printf("\t%s", ofile->sasm);
		ft_printf("\n");
	}
}

static void	print_sasm_32(t_ofile *ofile)
{
	if (ofile->sasm != NULL)
	{
		ft_printf("%08d", ofile->swap(ofile, ofile->mh->filetype) - 1);
		print_addr(ofile->swap(ofile,\
			ofile->section_text->addr) + ofile->length);
		ft_printf("\tasmtab[%2d][%2d] byte(%3d)",\
			ofile->opcode1, ofile->opcode2, ofile->byte);
		ft_printf("\t%s", ofile->sasm);
		ft_printf("\n");
	}
}

void		ftv_otool64(t_ofile *ofile)
{
	ft_printf("(__TEXT,__text) section\n");
	load_section_text_64(ofile);
	load_section_sym_64(ofile);
	if (ofile->section_text64 == NULL)
		return ;
	ofile->length = 0;
	ofile->ptr = ofile->map + ofile->swap(ofile, ofile->section_text64->offset);
	ofile->arraylist_64 = ofile->map + ofile->symtab->symoff;
	while (ofile->length < ofile->swap(ofile, ofile->section_text64->size))
	{
		load_dp(ofile);
		get_function_name_by_pointer_64((ofile->swap(ofile,\
			ofile->section_text64->addr) + ofile->length), ofile);
		desable_opcode(ofile, ofile->swap(ofile, ofile->section_text64->size));
		print_sasm_64(ofile);
		ofile->length++;
	}
}

void		ftv_otool32(t_ofile *ofile)
{
	ft_printf("(__TEXT,__text) section\n");
	load_section_text_32(ofile);
	load_section_sym_32(ofile);
	if (ofile->section_text == NULL)
		return ;
	ofile->length = 0;
	ofile->ptr = ofile->map + ofile->swap(ofile, ofile->section_text->offset);
	ofile->arraylist_32 = ofile->map + ofile->symtab->symoff;
	while (ofile->length < ofile->swap(ofile, ofile->section_text->size))
	{
		load_dp(ofile);
		get_function_name_by_pointer_32((ofile->swap(ofile,\
			ofile->section_text->addr) + ofile->length), ofile);
		desable_opcode(ofile, ofile->swap(ofile, ofile->section_text->size));
		print_sasm_32(ofile);
		ofile->length++;
	}
}
