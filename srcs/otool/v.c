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

int			get_function_name_by_pointer(int ptr, t_ofile *ofile)
{
	int		i;
	char	*function_name;

	i = 0;
	while (i < (int)ofile->symtab->nsyms)
	{
		if (ofile->arraylist_64[i].n_un.n_strx >= 1 
			&& ofile->arraylist_64[i].n_sect >= 0)
		{
			if ((int)ofile->arraylist_64[i].n_value == ptr)
			{
				function_name = ofile->map +\
				ofile->symtab->stroff + ofile->arraylist_64[i].n_un.n_strx;
				if (function_name != NULL && ft_strlen(function_name) > 0)
				{
					ft_printf("%s:\n", function_name);
					return (1);
				}
			}
		}
		i++;
	}
	return (0);
}

unsigned long	get_value(unsigned long size, char *sect, unsigned long length, unsigned long left)
{
	unsigned long i;
	unsigned long value;
	unsigned char byte;

	value = 0;
	i = 0;
	while (i < size)
	{
		byte = 0;
		if (left > 0)
		{
			byte = sect[length + left];
		}
		value |= (unsigned long)byte << (8 * i);
		i++;
	}
	return (value);
}

void modrm_byte(unsigned long *mode, unsigned long *reg, unsigned long *r_m, unsigned char byte)
{
	*r_m = byte & 0x7;
	*reg = byte >> 3 & 0x7;
	*mode = byte >> 6 & 0x3;
}

char	*desable_opcode(char *ptr, size_t size, size_t i, size_t *offset)
{
	unsigned char byte;
	char *tmp;
	unsigned opcode1, opcode2, opcode3, opcode4, opcode5;
	const struct instable *dp;
	unsigned long r_m, mode;

	(void)offset;
	tmp = NULL;
	if (i > size)
		return (NULL);
	byte = get_value(sizeof(char), ptr, i, *offset);
	if (byte == 0)
		return (NULL);
	opcode1 = byte >> 4 & 0xf;
	opcode2 = byte & 0xf;
	dp = &distable[opcode1][opcode2];
	if(dp->adr_mode == PREFIX)
		ft_asprintf(&tmp, "%s", dp->name);
	else if(dp->adr_mode == OVERRIDE)
		ft_asprintf(&tmp, "%s", dp->name);
	else
	{
		if(dp->indirect == (const struct instable *)op0F)
		{
			(*offset)++;
		    byte = get_value(sizeof(char), ptr, i, *offset);
		    opcode4 = byte >> 4 & 0xf;
		    opcode5 = byte & 0xf;
		    if(opcode4 > 12)
		    {
				ft_printf(".byte 0x%01x%01x, 0x%01x%01x #bad opcode\n",
			       	(unsigned int)opcode1, (unsigned int)opcode2,
			       	(unsigned int)opcode4, (unsigned int)opcode5);
				return(NULL);
	    	}
	    	dp = &op0F[opcode4][opcode5];
	    	ft_asprintf(&tmp, "%s", dp->name);
		}
		if(dp->indirect != TERM)
		{
			(*offset)++;
		    byte = get_value(sizeof(char), ptr, i, *offset);
		    modrm_byte(&mode, (unsigned long *)&opcode3, &r_m, byte);
		    if(opcode1 == 0xD && opcode2 >= 0x8)
		    {
				if(opcode2 == 0xB && mode == 0x3 && opcode3 == 4)
				    dp = &opFP5[r_m];
				else if(opcode2 == 0xB && mode == 0x3 && opcode3 > 4){
				    ft_printf(".byte 0x%01x%01x, 0x%01x%01x 0x%02x #bad opcode\n",
					   (unsigned int)opcode1, (unsigned int)opcode2,
					   (unsigned int)opcode4, (unsigned int)opcode5,
					   (unsigned int)byte);
				    return(NULL);
				}
				else if(opcode2 == 0x9 && mode == 0x3 && opcode3 >= 4)
				    dp = &opFP4[opcode3-4][r_m];
				else if(mode == 0x3)
				    dp = &opFP3[opcode2-8][opcode3];
				else
				    dp = &opFP1n2[opcode2-8][opcode3];
		    }
		    else
			dp = dp->indirect + opcode3;
		}
		if(dp->indirect != TERM)
		{
	    	ft_asprintf(&tmp, ".byte 0x%02x #bad opcode", (unsigned int)byte);
		}
		if(dp->adr_mode != CBW && dp->adr_mode != CWD)
		{
		    if(dp->suffix)
		    {
				//if(data16 == TRUE)
				//	ft_asprintf(&tmp, "%sw", dp->name);
				//else
				    ft_asprintf(&tmp, "%sl", dp->name);
		    }
		    else
				ft_asprintf(&tmp, "%s", dp->name);
		}
	}

	return (tmp);
}

void		ftv_otool64(t_ofile *ofile)
{
	size_t	i;
	size_t 	offset;
	void	*ptr;
	char	*opcode;

	ft_printf("(__TEXT,__text) section\n");
	load_section_text_64(ofile);
	load_section_sym_64(ofile);
	if (ofile->section_text64 == NULL)
		return ;
	i = 0;
	ptr = ofile->map + ofile->swap(ofile, ofile->section_text64->offset);
	ofile->arraylist_64 = ofile->map + ofile->symtab->symoff;
	while (i < ofile->swap(ofile, ofile->section_text64->size))
	{
		offset = 0;
		if (get_function_name_by_pointer((ofile->swap(ofile, ofile->section_text64->addr) + i), ofile))
		{
			ft_printf("%08d", ofile->swap(ofile, ofile->mh64->filetype) - 1);
			print_addr(ofile->swap(ofile, ofile->section_text64->addr) + i + offset);
			ft_printf("\tpushq	%%rbp\n");
			offset++;
		}
		while (offset < 16)
		{
			opcode = desable_opcode(ptr, ofile->swap(ofile, ofile->section_text64->size), i, &offset);
			if (opcode != NULL)
			{
				ft_printf("%08d", ofile->swap(ofile, ofile->mh64->filetype) - 1);
				print_addr(ofile->swap(ofile, ofile->section_text64->addr) + i + offset);
				ft_printf("\t%s", opcode);
				ft_printf("\n");
			}
			offset++;
		}
		i += 16;
	}
}

void		ftv_otool32(t_ofile *ofile)
{
	size_t	i;
	void	*ptr;

	ft_printf("(__TEXT,__text) section\n");
	load_section_text_32(ofile);
	load_section_sym_32(ofile);
	if (ofile->section_text == NULL)
		return ;
	i = 0;
	ofile->arraylist_64 = ofile->map + ofile->symtab->symoff;
	ptr = ofile->map + ofile->swap(ofile, ofile->section_text->offset);
	while (i < ofile->swap(ofile, ofile->section_text->size))
	{
		print_addr(ofile->swap(ofile, ofile->section_text->addr) + i);
		ft_printf("\t");

		ft_printf("\n");
		i += 16;
	}
}
