/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_function_by_pointer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:14:06 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/13 09:14:07 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int			get_function_name_by_pointer_64(int ptr, t_ofile *ofile)
{
	int		i;
	char	*function_name;

	i = 0;
	while (i < (int)ofile->symtab->nsyms)
	{
		if (ofile->arraylist_64[i].n_un.n_strx >= 1 &&\
			ofile->arraylist_64[i].n_sect >= 0)
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

int			get_function_name_by_pointer_32(int ptr, t_ofile *ofile)
{
	int		i;
	char	*function_name;

	i = 0;
	while (i < (int)ofile->symtab->nsyms)
	{
		if (ofile->arraylist_32[i].n_un.n_strx >= 1 &&\
			ofile->arraylist_32[i].n_sect >= 0)
		{
			if ((int)ofile->arraylist_32[i].n_value == ptr)
			{
				function_name = ofile->map +\
				ofile->symtab->stroff + ofile->arraylist_32[i].n_un.n_strx;
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
