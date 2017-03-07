/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getname.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 17:33:25 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/07 17:33:26 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

char	*getname64(char *test, void *map, struct nlist_64 l64)
{
	char *name;

	name = NULL;
	if (l64.n_type == 15 && l64.n_sect == 1 && !(getflags(0) & flag_u))
	{
		ft_asprintf(&name, "%08d%08x T %s\n",\
			((struct mach_header_64*)map)->filetype - 1,\
			(unsigned int)l64.n_value, test);
	}
	else if (l64.n_type == 14 && l64.n_sect == 1 && !(getflags(0) & flag_u))
	{
		ft_asprintf(&name, "%08d%08x t %s\n",\
			((struct mach_header_64*)map)->filetype - 1,\
			(unsigned int)l64.n_value, test);
	}
	else if (l64.n_type == 1)
	{
		ft_asprintf(&name, "                 U %s\n", test);
	}
	return (name);
}

char	*getname32(char *test, struct nlist l32)
{
	char *name;

	name = NULL;
	if (l32.n_type == 15 && l32.n_sect == 1 && !(getflags(0) & flag_u))
	{
		ft_asprintf(&name, "        %08x T %s\n",\
			(unsigned int)l32.n_value, test);
	}
	else if (l32.n_type == 14 && l32.n_sect == 1 && !(getflags(0) & flag_u))
	{
		ft_asprintf(&name, "        %08x t %s\n",\
			(unsigned int)l32.n_value, test);
	}
	else if (l32.n_type == 1)
		ft_asprintf(&name, "                 U %s\n", test);
	return (name);
}
