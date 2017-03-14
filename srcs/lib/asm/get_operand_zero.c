/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operand_zero.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:20:25 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/13 09:20:26 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include "asm_i386.h"

BOOLEAN			get_s_i_b(t_ofile *ofile, unsigned long *ss,\
	unsigned long *base, unsigned long *index)
{
	if (ofile->r_m == ESP && ofile->mode != REG_ONLY && ofile->addr16 == false)
	{
		ofile->length++;
		ofile->byte = get_value(sizeof(char), ofile->ptr, ofile->length);
		modrm_byte(ss, index, base, ofile->byte);
		return (true);
	}
	return (false);
}

void			load_result(t_ofile *ofile)
{
	if (ofile->mode == REG_ONLY)
	{
		if (ofile->data16)
			ft_strcpy(ofile->result, g_reg16[ofile->r_m][ofile->wbit]);
		else
			ft_strcpy(ofile->result, g_reg32[ofile->r_m][ofile->wbit]);
	}
	else
	{
		if (ofile->r_m == EBP && ofile->mode == 0)
		{
			ofile->result = ft_strnew(0);
		}
		else
		{
			if (ofile->addr16 == true)
				ft_asprintf(&ofile->result, "(%s)",\
					g_regname16[ofile->mode][ofile->r_m]);
			else
				ft_asprintf(&ofile->result, "(%s)",\
					g_regname32[ofile->mode][ofile->r_m]);
		}
	}
}

void			get_operand_zero(t_ofile *ofile)
{
	int				s_i_b;
	unsigned long	ss;
	unsigned long	index;
	unsigned long	base;

	ofile->symadd0 = NULL;
	ofile->symsub0 = NULL;
	ofile->value0 = 0;
	ofile->value0_size = 0;
	ofile->result = ft_strnew(0);
	s_i_b = get_s_i_b(ofile, &ss, &base, &index);
	if (ofile->addr16)
		ofile->value0_size = g_dispsize16[ofile->r_m][ofile->mode];
	else
		ofile->value0_size = g_dispsize32[ofile->r_m][ofile->mode];
	if (s_i_b == true && ofile->mode == 0 && base == EBP)
		ofile->value0_size = sizeof(long);
	if (s_i_b == true)
		ft_asprintf(&ofile->result, "(%s%s,%s)",\
			g_regname32[ofile->mode][base],\
			g_indexname[index], g_scale_factor[ss]);
	else
		load_result(ofile);
}
