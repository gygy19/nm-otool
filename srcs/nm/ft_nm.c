/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 00:29:30 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/11 00:29:31 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void		select_sort(t_ofile *ofile, char **list)
{
	g_cmp = 11;
	if (ofile->flags == flag_x)
		g_cmp = 29;
	if ((ofile->flags & flag_o) != 0)
		g_cmp += ft_strlen(ofile->name) + 2;
	if (ofile->is_64)
		g_cmp += 9;
	ft_qsort(list, ofile->symtab->nsyms, "char*", cmp_nm);
}

void		sort_and_print(t_ofile *ofile, char **list)
{
	int i;
	int	left;

	select_sort(ofile, list);
	i = 0;
	left = 0;
	while (i < (int)ofile->symtab->nsyms)
	{
		if (list[i] != NULL && ft_strlen(list[i]) > 0)
		{
			ft_printf("%s", list[i] + left);
		}
		i++;
	}
	free(list);
}

void		ft_nm64(t_ofile *ofile)
{
	char	**list;
	int		i;

	i = 0;
	load_nsections(ofile);
	load_section_sym_64(ofile);
	if (ofile->symtab == NULL)
	{
		not_object_file(ofile->name, ofile->prog);
		return ;
	}
	if (!(list = (char**)malloc(sizeof(char*) * (int)ofile->symtab->nsyms)))
		return ;
	ofile->arraylist_64 = ofile->map + ofile->symtab->symoff;
	while (i < (int)ofile->symtab->nsyms)
	{
		list[i] = parse_nlist64(ofile, ofile->arraylist_64[i]);
		i++;
	}
	sort_and_print(ofile, list);
}

void		ft_nm32(t_ofile *ofile)
{
	char	**list;
	int		i;

	i = 0;
	load_nsections(ofile);
	load_section_sym_32(ofile);
	if (ofile->symtab == NULL)
	{
		not_object_file(ofile->name, ofile->prog);
		return ;
	}
	if (!(list = (char**)malloc(sizeof(char*) * (int)ofile->symtab->nsyms)))
		return ;
	ofile->arraylist_32 = ofile->map + ofile->symtab->symoff;
	while (i < (int)ofile->symtab->nsyms)
	{
		list[i] = parse_nlist32(ofile, ofile->arraylist_32[i]);
		i++;
	}
	sort_and_print(ofile, list);
}
