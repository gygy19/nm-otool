/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_operand_zero.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:22:26 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/13 09:22:28 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include "asm_i386.h"

void			print_operand_zero(t_ofile *ofile)
{
	if (ofile->symadd0 != NULL)
	{
	}
	else
	{
		if (ofile->value0_size != 0)
		{
			ft_asprintf(&ofile->sasm, "%s, %s%0x%s", ofile->sasm,\
				ofile->asmseg, ofile->value0, ofile->result);
		}
		else
			ft_asprintf(&ofile->sasm, "%s, %s%s", ofile->sasm,\
				ofile->asmseg, ofile->result);
	}
}
