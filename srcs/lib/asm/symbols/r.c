/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:32:37 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/13 09:32:39 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include "asm_i386.h"

int		asm_r(t_ofile *ofile)
{
	const char *reg_name;

	ofile->reg = REGNO(ofile->opcode2);
	if (ofile->data16 == true)
		reg_name = g_reg16[ofile->reg][LONGOPERAND];
	else
		reg_name = g_reg32[ofile->reg][LONGOPERAND];
	ft_asprintf(&ofile->sasm, "%s\t%s", ofile->sasm, reg_name);
	return (1);
}
