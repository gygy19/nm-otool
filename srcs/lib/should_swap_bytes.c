/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   should_swap_bytes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 19:43:25 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/01 19:43:26 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int		should_swap_bytes(uint32_t magic)
{
	return (magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM);
}
