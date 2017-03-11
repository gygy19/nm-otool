/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ofile_sections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 23:01:42 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/10 23:01:44 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int			load_section_text_64(t_ofile *ofile)
{
	int i;

	i = 0;
	ofile->section_text64 = NULL;
	while (i < (int)ofile->swap(ofile, ofile->mh64->ncmds))
	{
		if (ft_strcmp(ofile->sec64[i]->segname, SEG_TEXT) == 0)
		{
			ofile->section_text64 = ofile->sec64[i];
			return (i);
		}
		i++;
	}
	return (0);
}

int			load_section_text_32(t_ofile *ofile)
{
	int i;

	i = 0;
	ofile->section_text = NULL;
	while (i < (int)ofile->swap(ofile, ofile->mh->ncmds))
	{
		if (ft_strcmp(ofile->sec[i]->segname, SEG_TEXT) == 0)
		{
			ofile->section_text = ofile->sec[i];
			return (i);
		}
		i++;
	}
	return (0);
}

int			load_section_sym_64(t_ofile *ofile)
{
	int i;

	i = 0;
	ofile->symtab = NULL;
	while (i < (int)ofile->swap(ofile, ofile->mh64->ncmds))
	{
		if (ofile->swap(ofile, ofile->cmd[i]->cmd) == LC_SYMTAB)
		{
			ofile->symtab = (void*)ofile->cmd[i];
			return (i);
		}
		i++;
	}
	return (0);
}

int			load_section_sym_32(t_ofile *ofile)
{
	int i;

	i = 0;
	ofile->symtab = NULL;
	while (i < (int)ofile->swap(ofile, ofile->mh->ncmds))
	{
		if (ofile->swap(ofile, ofile->cmd[i]->cmd) == LC_SYMTAB)
		{
			ofile->symtab = (void*)ofile->cmd[i];
			return (i);
		}
		i++;
	}
	return (0);
}
