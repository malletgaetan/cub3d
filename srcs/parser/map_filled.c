/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_filled.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:56:32 by tbatteux          #+#    #+#             */
/*   Updated: 2023/07/31 10:56:34 by tbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W')
		return (1);
	return (0);
}

int	map_filled(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (valid(map[i - 1][j]) || valid(map[i + 1][j])
						|| valid(map[i][j - 1]) || valid(map[i][j + 1]))
					return (1);
			}
			j++;
		}
	}
	return (0);
}
