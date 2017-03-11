/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_function_by_os.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 22:39:26 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/10 22:39:28 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	select_function_by_os(t_ofile *ofile,\
	void (*function64)(t_ofile *ofile), void (*function32)(t_ofile *ofile))
{
	if (ofile->is_64)
		function64(ofile);
	else if (ofile->is_32)
		function32(ofile);
}
