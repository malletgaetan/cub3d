/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:08:10 by tbatteux          #+#    #+#             */
/*   Updated: 2023/07/28 17:09:30 by tbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**which_cardinal(t_conf *info, int x)
{
	if (x == 1)
		return (&(info->north));
	else if (x == 2)
		return (&(info->south));
	else if (x == 3)
		return (&(info->west));
	else
		return (&(info->east));
}

void	recup_texture(char *txt, char *find, int x)
{
	int			i;
	int			j;
	char		**tmp;

	i = -1;
	while (txt[++i])
		if (txt[i] == find[0] && txt[i + 1] == find[1])
			break ;
	if (!txt[i])
		return ;
	i += 2;
	while (txt[i] && (txt[i] == ' ' || txt[i] == '	'))
		i++;
	j = i;
	while (txt[j] && txt[j] != '\n')
		j++;
	tmp = which_cardinal(&(g_conf), x);
	*tmp = gc_malloc(&(g_gc), (j - i + 1) * sizeof(char));
	j = 0;
	while (txt[i] && txt[i] != '\n')
		(*tmp)[j++] = txt[i++];
	(*tmp)[j] = 0;
}
