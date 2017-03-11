/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_ofile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 22:16:20 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/10 22:16:21 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static void	load_segment_64(t_ofile *ofile)
{
	void	*ptr;
	int		i;

	i = 0;
	if (ofile->is_64 == false)
		return ;
	ofile->cmd = malloc(sizeof(struct load_command) *\
		ofile->swap(ofile, ofile->mh64->ncmds));
	ofile->sec64 = malloc(sizeof(struct load_command) *\
		ofile->swap(ofile, ofile->mh64->ncmds));
	if (ofile->cmd == NULL || ofile->sec64 == NULL)
	{
		ofile->error = true;
		return ;
	}
	ofile->seg64 = (void*)ofile->cmd;
	ptr = (ofile->map + sizeof(struct mach_header_64));
	while (i < (int)ofile->swap(ofile, ofile->mh64->ncmds))
	{
		ofile->cmd[i] = ptr;
		ofile->sec64[i] = (void*)(ptr + sizeof(struct segment_command_64));
		ptr += ofile->swap(ofile, ofile->cmd[i]->cmdsize);
		i++;
	}
}

static void	load_segment_32(t_ofile *ofile)
{
	void	*ptr;
	int		i;

	i = 0;
	if (ofile->is_32 == false)
		return ;
	ofile->cmd = malloc(sizeof(struct load_command) *\
		ofile->swap(ofile, ofile->mh->ncmds));
	ofile->sec = malloc(sizeof(struct load_command) *\
		ofile->swap(ofile, ofile->mh->ncmds));
	if (ofile->cmd == NULL || ofile->sec == NULL)
	{
		ofile->error = true;
		return ;
	}
	ofile->seg = (void*)ofile->cmd;
	ptr = (ofile->map + sizeof(struct mach_header));
	while (i < (int)ofile->swap(ofile, ofile->mh->ncmds))
	{
		ofile->cmd[i] = ptr;
		ofile->sec[i] = (struct section*)(ptr + sizeof(struct segment_command));
		ptr += ofile->swap(ofile, ofile->cmd[i]->cmdsize);
		i++;
	}
}

static void	load_ofile(t_ofile *ofile)
{
	uint32_t	magic;

	if (ofile->error == true)
		return ;
	magic = get_magic(ofile->map);
	ofile->is_32 = is_magic_32(magic);
	ofile->is_64 = is_magic_64(magic);
	ofile->is_swap = should_swap_bytes(magic);
	ofile->mh64 = (struct mach_header_64*)ofile->map;
	ofile->mh = (struct mach_header*)ofile->map;
	ofile->cmd = NULL;
	ofile->sec = NULL;
	ofile->sec64 = NULL;
	load_segment_64(ofile);
	load_segment_32(ofile);
}

static void	load_universal_ofile(t_ofile *ofile)
{
	if (ofile->is_universal == false)
		return ;
	ofile->fat = (struct fat_header*)ofile->map;
	if (ofile->swap(ofile, ofile->fat->nfat_arch) == 0)
	{
		ofile->error = true;
		return ;
	}
	ofile->arch32 = ofile->map + sizeof(struct fat_header);
	ofile->arch64 = ofile->map + sizeof(struct fat_header)\
		+ sizeof(struct fat_arch);
	ofile->map = ofile->map + ofile->swap(ofile, ofile->arch64->offset);
}

t_ofile		*process_ofile(char *file, int fd, struct stat st, char *prog)
{
	t_ofile		*ofile;
	uint32_t	magic;

	if (!(ofile = malloc(sizeof(struct s_ofile))))
		return (NULL);
	if ((ofile->map = ft_mmap(fd, st.st_size)) == MAP_FAILED)
	{
		permission_denied(file, prog);
		return (NULL);
	}
	magic = get_magic(ofile->map);
	ofile->error = false;
	ofile->is_universal = is_magic_universal(magic);
	ofile->is_32 = is_magic_32(magic);
	ofile->is_64 = is_magic_64(magic);
	ofile->is_swap = should_swap_bytes(magic);
	ofile->swap = ft_osswapconstint32;
	load_universal_ofile(ofile);
	load_ofile(ofile);
	if (ofile->error == true)
	{
		permission_denied(file, prog);
		return (NULL);
	}
	return (ofile);
}
