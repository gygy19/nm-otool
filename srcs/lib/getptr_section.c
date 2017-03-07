/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getptr_section.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:48:22 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/03 10:48:24 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

char	*getptr_section(struct section *s32, struct section_64 *s64,\
	void *header, int is_64)
{
	char	*ptr;
	int		offset;

	if (is_64)
		offset = s64->offset;
	else
		offset = s32->offset;
	ptr = header + offset;
	return (ptr);
}
