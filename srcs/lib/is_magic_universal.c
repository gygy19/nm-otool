/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_magic_universal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 20:50:17 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/09 20:50:19 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int		is_magic_universal(uint32_t magic)
{
	return (magic == FAT_MAGIC || magic == FAT_CIGAM);
}
