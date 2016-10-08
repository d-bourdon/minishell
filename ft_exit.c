/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbourdon <dbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 12:18:22 by dbourdon          #+#    #+#             */
/*   Updated: 2016/10/08 14:55:55 by dbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tabtab(char **tab)
{
	int		i;

	i = 0;
	while (tab && tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

void	free_env(void)
{
	t_liste	*tmp;

	while (g_env)
	{
		free(g_env->nom);
		free(g_env->valeur);
		if (g_env->next)
		{
			tmp = g_env->next;
			free(g_env);
			g_env = tmp;
		}
		else
			break ;
	}
	free(g_env);
}

int		ft_exit(char **cmd)
{
	if (ft_strcmp(cmd[0], "exit") != 0)
		return (0);
	if (!cmd[1])
	{
		free_env();
		exit(0);
	}
	if (ft_strcmp(cmd[1], "666") == 0)
	{
		free_env();
		while (1)
		{
		}
	}
	if (!cmd[2])
	{
		free_env();
		exit(ft_atoi(cmd[1]));
	}
	ft_putstr("\033[31mExit : utilisation incorecte:\033[00m\n");
	ft_putstr("exit | exit [nombre] | exit 666 -> while(1) pour leaks\n");
	free_tabtab(cmd);
	return (1);
}
