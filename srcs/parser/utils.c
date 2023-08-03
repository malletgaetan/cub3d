/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:30:39 by tbatteux          #+#    #+#             */
/*   Updated: 2023/07/31 14:41:05 by tbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*final;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	final = gc_malloc(&(g_gc), (i + j + 1) * sizeof(char));
	if (!final)
		return (NULL);
	i = -1;
	while (s1[++i])
		final[i] = s1[i];
	j = -1;
	while (s2[++j])
		final[i + j] = s2[j];
	final[i + j] = 0;
	return (final);
}

int	ft_atoi(char *nptr)
{
	int	i;
	int	rst;
	int	cpt;

	i = 0;
	rst = 0;
	cpt = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			cpt = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		rst = rst * 10 + (nptr[i++] - '0');
	if (cpt == 1)
		rst = -rst;
	return (rst);
}

void	recup_pos(void)
{
	int	i;
	int	j;

	j = -1;
	while (g_conf.map[++j])
	{
		i = -1;
		while (g_conf.map[j][++i])
		{
			if (is_character(g_conf.map[j][i]))
			{
				g_gs.pos_y = i - 0.5;
				g_gs.pos_x = j - 0.5;
			}
		}
	}
}
