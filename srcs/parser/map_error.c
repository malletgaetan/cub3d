/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:56:24 by tbatteux          #+#    #+#             */
/*   Updated: 2023/07/31 10:56:25 by tbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	contour_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (j < t_line(map[i]))
		{
			while (map[i][j] && map[i][j] == ' ')
				j++;
			if (map[i][j] != '1')
				return (1);
			while (map[i][j] && map[i][j] != ' ')
				j++;
			if (map[i][j - 1] != '1')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_character(char c)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (1);
	return (0);
}

int	valid_char(char **map)
{
	int	cpt;
	int	i;
	int	j;

	i = -1;
	cpt = 0;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' ')
			{
				if (!is_character(map[i][j]))
					cpt++;
				else
					return (1);
			}
			j++;
		}
	}
	if (cpt != 1)
		return (1);
	return (0);
}

int	first_and_last(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (map[i][++j])
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (1);
	while (map[i + 1])
		i++;
	j = -1;
	while (map[i][++j])
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (1);
	return (0);
}

int	map_error(char **map)
{
	if (contour_map(map) || first_and_last(map))
	{
		printf("Error: The map isn't correctly closed\n");
		return (1);
	}
	if (valid_char(map))
	{
		printf("Error: There are unsupported characters ");
		printf("or two starting points in the map\n");
		return (1);
	}
	if (map_filled(map))
	{
		printf("Error: The map isn't correctly filled/closed\n");
		return (1);
	}
	return (0);
}
