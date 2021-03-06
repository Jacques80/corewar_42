/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_02e_check_file_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 20:26:54 by llopez            #+#    #+#             */
/*   Updated: 2019/04/12 11:19:27 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

int		ft_cbc(char *file, char a, char b)
{
	while (file && *file)
	{
		if (*file == b)
			return (0);
		if (*file == a)
			return (1);
		file++;
	}
	return (0);
}

void	delete_comment(char *str)
{
	while (str && *str)
	{
		if (*str == '#')
		{
			while (*str && *str != '\n')
			{
				*str = ' ';
				str++;
			}
		}
		str++;
	}
}

char	*jump_spaces(char *file)
{
	while (ft_isalnum(*file))
		file++;
	while (ft_isspace(*file))
		file++;
	return (file);
}

char	*jump_str_declar(char *file, int max_size)
{
	int	i;

	if (!file)
		return (0);
	file = jump_spaces(file);
	if (*file != '"')
		return (0);
	i = 1;
	if (!ft_cbc(file + i, '"', '\n'))
		return (0);
	while (*(file + i) && *(file + i) != '"')
		i++;
	if (i + 1 > max_size)
		return (0);
	file += i + 1;
	return (file);
}
