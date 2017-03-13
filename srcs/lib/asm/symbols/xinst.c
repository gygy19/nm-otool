/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xinst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:31:12 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/13 09:31:14 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include "asm_i386.h"

int		asm_xinst(t_ofile *ofile)
{
	const char *reg_name;

	ofile->wbit = WBIT(ofile->opcode5);
	if (ofile->got_modrm_byte == false)
	{
		ofile->got_modrm_byte = true;
		ofile->length++;
		ofile->byte = get_value(sizeof(char), ofile->ptr, ofile->length);
		modrm_byte(&ofile->mode,\
			(unsigned long *)&ofile->reg, &ofile->r_m, ofile->byte);
	}
	get_operand(ofile, '0');
	if (ofile->data16 == true)
		reg_name = g_reg16[ofile->reg][ofile->wbit];
	else
		reg_name = g_reg32[ofile->reg][ofile->wbit];
	ft_asprintf(&ofile->sasm, "%s\t%s", ofile->sasm, reg_name);
	print_operand(ofile, '0');
	return (1);
}
