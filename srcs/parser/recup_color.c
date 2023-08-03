/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:13:14 by tbatteux          #+#    #+#             */
/*   Updated: 2023/07/28 17:14:04 by tbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_overflow(int *tmp, int x)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (tmp[i] > 255 || tmp[i] < 0)
		{
			if (x == 1)
				printf("Error: invalid color for the ceiling\n");
			if (x == 2)
				printf("Error: invalid color for the floor\n");
			gc_clean(&(g_gc));
			return (1);
		}
		i++;
	}
	return (0);
}

int	recup_color_part2(char *txt, int **tmp, char find)
{
	int	i;
	int	j;

	i = -1;
	while (txt[++i])
		if (txt[i] == find && txt[i + 1] == ' ')
			break ;
	if (!txt[i])
		return (1);
	i += 2;
	*tmp = gc_malloc(&(g_gc), 4 * sizeof(int));
	j = -1;
	while (++j < 3 && txt[i] != '\n')
	{
		(*tmp)[j] = ft_atoi(&txt[i]);
		while (txt[i] >= '0' && txt[i] <= '9')
			i++;
		while (txt[i + 1] != '\n' && (txt[i] < '0' && txt[i] > '9'))
			i++;
		i++;
	}
	(*tmp)[j] = 0;
	return (0);
}

int	recup_color(char *txt, char find, int x)
{
	int	*tmp;

	if (recup_color_part2(txt, &tmp, find))
	{
		printf("Error: There is no color for the ceiling or the floor\n");
		return (1);
	}
	if (color_overflow(tmp, x))
		return (1);
	if (x == 1)
		g_conf.cell_color = tmp[0] * 256 * 256 + tmp[1] * 256 + tmp[2];
	else if (x == 2)
		g_conf.floor_color = tmp[0] * 256 * 256 + tmp[1] * 256 + tmp[2];
	return (0);
}
