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

char	*getptr_section(struct section_64 *section, void *header)
{
	char	*ptr;

	ptr = header + section->offset;
	return (ptr);
}
