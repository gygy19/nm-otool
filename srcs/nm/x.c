/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 09:50:05 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/11 09:50:07 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

char	*get_name_x_64(t_ofile *ofile, char *test, struct nlist_64 l64)
{
	char *name;

	if (l64.n_type & N_STAB)
		return (NULL);
	name = NULL;
	(void)ofile;
	(void)test;
	ft_asprintf(&name, "%08lx%08lx %02x %02x %04x ", get_file_type(ofile),
		l64.n_value,
		(unsigned int)(l64.n_type & 0xff),
		(unsigned int)(l64.n_sect & 0xff),
		(unsigned int)(l64.n_desc & 0xffff));
	ft_asprintf(&name, "%s%08x %s\n", name,\
		(unsigned int)l64.n_un.n_strx, test);
	return (name);
}

char	*get_name_x_32(t_ofile *ofile, char *test, struct nlist l32)
{
	char *name;

	if (l32.n_type & N_STAB)
		return (NULL);
	name = NULL;
	(void)ofile;
	(void)test;
	ft_asprintf(&name, "%08lx %02x %02x %04x ", l32.n_value,
		(unsigned int)(l32.n_type & 0xff),
		(unsigned int)(l32.n_sect & 0xff),
		(unsigned int)(l32.n_desc & 0xffff));
	ft_asprintf(&name, "%s%08x %s\n", name,\
		(unsigned int)l32.n_un.n_strx, test);
	return (name);
}
