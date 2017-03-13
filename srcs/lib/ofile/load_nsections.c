/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_nsections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 02:13:09 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/11 02:13:10 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void		load_nsections(t_ofile *ofile)
{
	if (ofile->is_64)
	{
		ofile->text_nsect = load_section_name_64(ofile, SECT_TEXT, SEG_TEXT);
		ofile->data_nsect = load_section_name_64(ofile, SECT_DATA, SEG_DATA);
		ofile->bss_nsect = load_section_name_64(ofile, SECT_BSS, SEG_DATA);
	}
	else if (ofile->is_32)
	{
		ofile->text_nsect = load_section_name_32(ofile, SECT_TEXT, SEG_TEXT);
		ofile->data_nsect = load_section_name_32(ofile, SECT_DATA, SEG_DATA);
		ofile->bss_nsect = load_section_name_32(ofile, SECT_BSS, SEG_DATA);
	}
}

int			load_section_name_64(t_ofile *ofile, char *sectname, char *segn)
{
	int	i;
	int	n;
	int	j;

	i = 0;
	n = 0;
	while (i < (int)ofile->swap(ofile, ofile->mh64->ncmds))
	{
		if (ofile->cmd[i]->cmd == LC_SEGMENT_64)
		{
			j = 0;
			while (j < (int)ofile->seg64[i]->nsects)
			{
				ft_printf("%s, %s\n", (j + ofile->sec64[i])->sectname, (j + ofile->sec64[i])->segname);
				if ((ft_strcmp((j + ofile->sec64[i])->sectname, sectname) == 0)
					&& (ft_strcmp((j + ofile->sec64[i])->segname, segn) == 0))
				{
					return (n + 1);
				}
				j++;
				n++;
			}
		}
		i++;
	}
	return (0);
}

int			load_section_name_32(t_ofile *ofile, char *sectname, char *segn)
{
	int	i;
	int	n;
	int	j;

	i = 0;
	n = 0;
	while (i < (int)ofile->swap(ofile, ofile->mh->ncmds))
	{
		if (ofile->cmd[i]->cmd == LC_SEGMENT)
		{
			j = 0;
			while (j < (int)ofile->seg[i]->nsects)
			{
				if ((ft_strcmp((j + ofile->sec[i])->sectname, sectname) == 0)
					&& (ft_strcmp((j + ofile->sec[i])->segname, segn) == 0))
				{
					return (n + 1);
				}
				j++;
				n++;
			}
		}
		i++;
	}
	return (0);
}
