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

int		get_file_type(t_ofile *ofile)
{
	if (ofile->is_64)
	{
		if (ofile->mh64->filetype == 2)
			return (1);
	}
	return (0);
}

char	parse_n_type_64(unsigned char c, struct nlist_64 list, t_ofile *ofile)
{
	if (c == N_UNDF)
	{
		if (list.n_value != 0)
			return ('c');
		return ('u');
	}
	if (c == N_PBUD)
		return ('u');
	if (c == N_ABS)
		return ('a');
	if (c == N_SECT)
	{
		if (list.n_sect == ofile->text_nsect)
			return ('t');
		else if (list.n_sect == ofile->data_nsect)
			return ('d');
		else if (list.n_sect == ofile->bss_nsect)
			return ('b');
		return ('s');
	}
	if (c == N_INDR)
		return ('i');
	return ('?');
}

char	parse_n_type_32(unsigned char c, struct nlist list, t_ofile *ofile)
{
	if (c == N_UNDF)
	{
		if (list.n_value != 0)
			return ('c');
		return ('u');
	}
	if (c == N_PBUD)
		return ('u');
	if (c == N_ABS)
		return ('a');
	if (c == N_SECT)
	{
		if (list.n_sect == ofile->text_nsect)
			return ('t');
		else if (list.n_sect == ofile->data_nsect)
			return ('d');
		else if (list.n_sect == ofile->bss_nsect)
			return ('b');
		return ('s');
	}
	if (c == N_INDR)
		return ('i');
	return ('?');
}

char	*getname64(t_ofile *ofile, char *test, struct nlist_64 l64)
{
	char *name;
	char character;

	if (l64.n_type & N_STAB)
		return (NULL);
	character = parse_n_type_64(l64.n_type & N_TYPE, l64, ofile);
	if ((ofile->flags & flag_u) && character != 'u')
		return (NULL);
	if ((l64.n_type & N_EXT) && character != '?')
		character = ft_toupper(character);
	name = ft_strdup("");
	if ((ofile->flags & flag_o))
	{
		ft_asprintf(&name, "%s: ", ofile->name);
	}
	if (!(ofile->flags & flag_u) && !(ofile->flags & flag_j))
	{
		if (character == 'u' || character == 'U' || character == 'i' || character == 'I')
			ft_asprintf(&name, "%s                ", name);
		else
		{
			//flag V
			ft_asprintf(&name, "%s%08lx%08lx", name, get_file_type(ofile), l64.n_value);
		}
		ft_asprintf(&name, "%s %c ", name, character);
	}
	ft_asprintf(&name, "%s%s\n", name, test);
	return (name);
}

char	*getname32(t_ofile *ofile, char *test, struct nlist l32)
{
	char *name;
	char character;

	if (l32.n_type & N_STAB)
		return (NULL);
	character = parse_n_type_32(l32.n_type & N_TYPE, l32, ofile);
	if ((ofile->flags & flag_u) && character != 'u')
		return (NULL);
	if ((l32.n_type & N_EXT) && character != '?')
		character = ft_toupper(character);
	name = ft_strdup("");
	if ((ofile->flags & flag_o))
	{
		ft_asprintf(&name, "%s: ", ofile->name);
	}
	if (!(ofile->flags & flag_u) && !(ofile->flags & flag_j))
	{
		if (character == 'u' || character == 'U' || character == 'i' || character == 'I')
			ft_asprintf(&name, "%s        ", name);
		else
		{
			//flag V
			ft_asprintf(&name, "%s%08lx", name, (unsigned int)l32.n_value);
		}
		ft_asprintf(&name, "%s %c ", name, character);
	}
	ft_asprintf(&name, "%s%s\n", name, test);
	return (name);
}
