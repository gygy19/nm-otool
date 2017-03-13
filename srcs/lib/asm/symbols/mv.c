/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:31:19 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/13 09:31:20 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include "asm_i386.h"

int		asm_mv(t_ofile *ofile)
{
	unsigned long	vbit;
	const char		*reg_name;

	vbit = VBIT(ofile->opcode2);
	ofile->wbit = WBIT(ofile->opcode2);
	get_operand(ofile, '0');
	reg_name = vbit ? "%cl" : "";
	ft_asprintf(&ofile->sasm, "%s\t%s", ofile->sasm, reg_name);
	print_operand(ofile, '0');
	return (1);
}
