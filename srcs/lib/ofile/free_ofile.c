/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ofile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 22:21:01 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/10 22:21:02 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void		free_ofile(t_ofile *ofile)
{
	if (ofile->cmd != NULL)
		free(ofile->cmd);
	if (ofile->is_64 && ofile->sec64 != NULL)
		free(ofile->sec64);
	else if (ofile->is_32 && ofile->sec != NULL)
		free(ofile->sec);
	free(ofile);
}
