/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_05_translate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:56:00 by llopez            #+#    #+#             */
/*   Updated: 2019/04/12 17:34:54 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

uint8_t		*add_byte(uint8_t content, t_binary *bin)
{
	size_t	i;
	uint8_t	*tmp;

	i = 0;
	tmp = (uint8_t *)ft_memalloc(sizeof(uint8_t) * (bin->size + 1));
	while (i < bin->size && bin->table)
	{
		tmp[i] = bin->table[i];
		i++;
	}
	bin->size++;
	tmp[i] = content;
	free(bin->table);
	return (tmp);
}

uint8_t		param_encode(char **param)
{
	int		i;
	uint8_t	content;

	content = 0x0;
	i = 0;
	while (param[i])
	{
		if (param[i][0] == DIRECT_CHAR)
			content |= DIR_CODE;
		else if (ft_isdigit(param[i][0]) || (param[i][0] == '-'\
			&& ft_isdigit(param[i][1])))
			content |= IND_CODE;
		else if (param[i][0] == 'r' && ft_atoi(&param[i][1]) <= REG_NUMBER)
			content |= REG_CODE;
		else if (param[i][0] == LABEL_CHAR)
			content |= IND_CODE;
		else
			return (0);
		i++;
		if (param[i])
			content = content << 2;
	}
	return (content);
}

uint8_t		*add_dir(int value, int little_dir, t_binary *bin)
{
	if (!little_dir)
	{
		bin->table = add_byte((value & 0xFF000000) >> 24, bin);
		bin->table = add_byte((value & 0x00FF0000) >> 16, bin);
	}
	bin->table = add_byte((value & 0x0000FF00) >> 8, bin);
	bin->table = add_byte((value & 0x000000FF), bin);
	return (bin->table);
}

uint8_t		*add_ind(int value, t_binary *bin)
{
	bin->table = add_byte((value & 0xFF00) >> 8, bin);
	bin->table = add_byte((value & 0x00FF), bin);
	return (bin->table);
}

int			get_right_value(char **param, int i, char **data, size_t b_bytes)
{
	int	value;

	value = 0;
	if (param[i][0] == DIRECT_CHAR)
		value = (param[i][1] == LABEL_CHAR) ? label_pos(param[i], data)\
			- (int)b_bytes : ft_atoi(&param[i][1]);
	else if (param[i][0] == LABEL_CHAR || (ft_isdigit(param[i][0])\
		|| (param[i][0] == '-' && ft_isdigit(param[i][1]))))
		value = (param[i][0] == LABEL_CHAR) ? label_pos(&param[i][0], data)\
			- (int)b_bytes : ft_atoi(param[i]);
	return (value);
}
