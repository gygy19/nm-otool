/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sym.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 17:33:48 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/07 17:33:50 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static void	sortandprint(struct symtab_command *symtab, char **list, int is_64)
{
	int i;
	int	left;

	ft_qsort(list, symtab->nsyms, "char*", cmpstringp);
	i = 0;
	left = 0;
	if ((getflags(0) & flag_u))
		left = 19;
	else if ((getflags(0) & flag_j))
		left = 19;
	else if (is_64 == 0)
		left = 8;
	while (i < (int)symtab->nsyms)
	{
		if (list[i] != NULL && ft_strlen(list[i]) > 0)
		{
			ft_printf("%s", list[i] + left);
		}
		i++;
	}
	free(list);
}

void		parse_sym64(struct load_command *cmd, void *ptr, void *map)
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
		list[i] = parse_nlist64(map, symtab, array[i]);
		i++;
	}
	sortandprint(symtab, list, 1);
}

void		parse_sym32(struct load_command *cmd, void *ptr, void *map)
{
	struct symtab_command	*symtab;
	struct nlist			*array;
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
		list[i] = parse_nlist32(map, symtab, array[i]);
		i++;
	}
	sortandprint(symtab, list, 0);
}
