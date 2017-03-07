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

char	*parse_nlist64(void *map, struct symtab_command *symtab,\
	struct nlist_64 l64)
{
	char *test;

	if (l64.n_un.n_strx >= 1 && l64.n_sect >= 0)
	{
		test = map + symtab->stroff + l64.n_un.n_strx;
		if (test != NULL && ft_strlen(test) > 0)
		{
			return (getname64(test, map, l64));
		}
	}
	return (NULL);
}

char	*parse_nlist32(void *map, struct symtab_command *symtab,\
	struct nlist l32)
{
	char *test;

	if (l32.n_un.n_strx >= 1 && l32.n_sect >= 0)
	{
		test = map + symtab->stroff + l32.n_un.n_strx;
		if (test != NULL && ft_strlen(test) > 0)
		{
			return (getname32(test, l32));
		}
	}
	return (NULL);
}
