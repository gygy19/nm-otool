/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 17:33:35 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/07 17:33:37 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

char	*parse_nlist64(t_ofile *ofile, struct nlist_64 l64)
{
	char *function_name;

	if (l64.n_un.n_strx >= 1 && l64.n_sect >= 0)
	{
		function_name = ofile->map + ofile->symtab->stroff + l64.n_un.n_strx;
		if (function_name != NULL && ft_strlen(function_name) > 0)
		{
			if (ofile->flags == flag_x)
				return (get_name_x_64(ofile, function_name, l64));
			return (getname64(ofile, function_name, l64));
		}
	}
	return (NULL);
}

char	*parse_nlist32(t_ofile *ofile, struct nlist l32)
{
	char *function_name;

	if (l32.n_un.n_strx >= 1 && l32.n_sect >= 0)
	{
		function_name = ofile->map + ofile->symtab->stroff + l32.n_un.n_strx;
		if (function_name != NULL && ft_strlen(function_name) > 0)
		{
			if (ofile->flags == flag_x)
				return (get_name_x_32(ofile, function_name, l32));
			return (getname32(ofile, function_name, l32));
		}
	}
	return (NULL);
}
