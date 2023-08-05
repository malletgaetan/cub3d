/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:15:07 by tbatteux          #+#    #+#             */
/*   Updated: 2023/07/28 17:15:42 by tbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	taille_map(char *map)
{
	int	i;
	int	cpt;

	cpt = 0;
	i = -1;
	while (map[++i])
	{
		if (map[i] == '\n' && (map[i - 1] == '\n' || !map[i - 1]))
			break ;
		if (map[i] == '\n')
			cpt++;
	}
	return (cpt);
}

int	t_line(char *map)
{
	int	i;

	i = 0;
	while (map[i] && map[i] != '\n')
		i++;
	return (i);
}

int	stocker_map(char *txt)
{
	int	i;
	int	j;
	int	x;

	x = 0;
	j = 0;
	i = -1;
	while (txt[++i])
	{
		x = 0;
		if (txt[i] == '\n' && (txt[i + 1] == '\n' || !txt[i + 1]))
			break ;
		if (txt[i] != '1' && txt[i] != ' ' && txt[i] != '0')
			break ;
		g_conf.map[j] = gc_malloc(&(g_gc), (t_line(&txt[i]) + 1) * 1);
		while (txt[i] && txt[i] != '\n')
			g_conf.map[j][x++] = txt[i++];
		g_conf.map[j][x] = 0;
		j++;
	}
	g_conf.map[j] = NULL;
	if (txt[i])
		if (printf("error: the map isn't the last parameter in the .cub\n"))
			return (1);
	return (0);
}

int	recup_map(char *txt)
{
	int	i;

	i = -1;
	while (txt[++i])
		if ((txt[i] == '1' || txt[i] == '0')
			&& (txt[i + 1] == '1' || txt[i + 1] == '\n')
			&& (txt[i - 1] == ' ' || txt[i - 1] == '\n' || txt[i - 1] == '\t'))
			break ;
	if (txt[i - 1] == ' ')
	{
		while (--i > 0)
			if (txt[i - 1] == '\n')
				break ;
	}
	g_conf.map = gc_malloc(&(g_gc), (taille_map(&txt[i]) + 1) * sizeof(char *));
	if (stocker_map(&txt[i]) == 1)
		return (1);
	return (0);
}
