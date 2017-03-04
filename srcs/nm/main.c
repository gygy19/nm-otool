/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:52:11 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/27 19:52:13 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int cmpstringp(const void *p1, const void *p2)
{
    return (ft_strcmp((char*)p1 + 19, (char*)p2 + 19));
}

char	*getname(char *test, void *map, struct nlist_64 list)
{
	char *name;

	name = NULL;
	if (list.n_type == 15 && list.n_sect == 1)
	{
		ft_asprintf(&name, "%08d%08x T %s\n",\
			((struct mach_header*)map)->filetype - 1, list.n_value, test);
	}
	else if (list.n_type == 14 && list.n_sect == 1)
	{
		ft_asprintf(&name, "%08d%08x t %s\n",\
			((struct mach_header*)map)->filetype - 1, list.n_value, test);
	}
	else if (list.n_type == 1)
		ft_asprintf(&name, "                 U %s\n", test);
	return (name);
}

char	*parse_nlist(void *map, struct symtab_command *symtab, struct nlist_64 list)
{
	char *test;

	if (list.n_un.n_strx >= 1 && list.n_sect >= 0)
	{
		test = map + symtab->stroff + list.n_un.n_strx;
		if (ft_strlen(test) > 0)
		{
			return (getname(test, map, list));
		}
	}
	return (NULL);
}

void	parse_sym(struct load_command *cmd, void *ptr, void* map)
{
	struct symtab_command	*symtab;
	struct nlist_64			*array;
	char					**list;
	int						i;

	symtab = ptr;
	i = 0;
	if (cmd->cmd != LC_SYMTAB)
		return ;
	if (!(list = (char**)malloc(sizeof(char*) * (int)symtab->nsyms)))
		return ;
	array = (map + symtab->symoff);
	while (i < (int)symtab->nsyms)
	{
		list[i] = parse_nlist(map, symtab, array[i]);
		i++;
	}
	ft_qsort(list, symtab->nsyms, "char*", cmpstringp);
	i = 0;
	while (i < (int)symtab->nsyms)
	{
		if (list[i] != NULL)
		{
			ft_printf("%s", list[i]);
			//free(list[i]);
		}
		i++;
	}
}

void	search_syms(char *file, void *map, int is_64)
{
	void						*header;
	uint32_t					i;
	struct load_command			*cmd;
	void						*ptr;

	header = map;
	(void)file;
	i = 0;
	if (is_64 == 1)
	{
		ptr = CASTHEADER_X64 + HEADER_OFFSET;
	}
	else
	{
		ptr = CASTHEADER_X32 + HEADER_OFFSET;
		swap_mach_header_32(CASTHEADER_X32);
	}
	while (WHILE_CMDS)
	{
		cmd = (struct load_command*)ptr;
		parse_sym(cmd, ptr, map);
		ptr += cmd->cmdsize;
		i++;
	}
}

int		check_flags(int argc, char **argv, int *flags)
{
	int i;
	int o;

	*flags = 0;
	i = 1;
	while (i < argc)
	{
		o = 0;
		while (argv[i][o] != '\0')
		{
			if (argv[i][0] != '-')
				break ;
			if (IS_FLAG_U && !(*flags & flag_u))
				*flags += flag_h;
			if (IS_FLAG_T && !(*flags & flag_t))
				*flags += flag_t;
			o++;
		}
		if (IS_FLAG_VERSION && !(*flags & flag_version))
			*flags += flag_version;
		i++;
	}
	return (*flags > 0);
}

int		inspect_file(char *file, int flags, char *prog)
{
	void		*map;
	struct stat	st;
	int			fd;

	if (!fileexists(file))
		return (nosuchfile(file, prog));
	if (isdir(file))
		return (isdirectory(file, prog));
	if (!is_regular(file))
		return (notobjectfile(file, prog));
	if ((fd = open(file, O_RDONLY)) < 3)
		return (permissiondenied(file, prog));
	fstat(fd, &st);
	if ((map = ft_mmap(fd, st.st_size)) == MAP_FAILED)
		return (permissiondenied(file, prog));
	if (((struct mach_header_64*)map)->filetype > 3
		|| ((struct mach_header_64*)map)->filetype < 1)
		return (notobjectfile(file, prog));
	if (flags == 0)
		search_syms(file, map, is_magic_64(get_magic(map)));
	return (0);
}

void	print_version(void *map)
{
	(void)map;
}

int		main(int argc, char **argv)
{
	int			flags;
	int			i;
	int			count;

	i = 1;
	count = 0;
	if (!check_flags(argc, argv, &flags) && argc == 1)
		return (printflags(argv[0]));
	if (flags & flag_version)
	{
		print_version(argv[0]);
		return (0);
	}
	while (i < argc)
	{
		if (argv[i][0] != '-')
		{
			inspect_file(argv[i], flags, argv[0]);
			count++;
		}
		i++;
	}
	return (0);
}
