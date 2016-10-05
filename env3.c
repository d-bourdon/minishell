/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbourdon <dbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 10:57:28 by dbourdon          #+#    #+#             */
/*   Updated: 2016/09/21 19:46:21 by dbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_liste	*ft_ajout_liste(char *base)
{
	t_liste	*ajout;
	char	**tmp;

	ajout = (t_liste*)malloc(sizeof(t_liste) * 1);
	tmp = ft_strsplit(base, '=');
	ajout->nom = ft_strdupfree(ft_strjoin(tmp[0], "\0"));
	ajout->valeur = ft_strdupfree(ft_strjoin(tmp[1], "\0"));
	ajout->next = NULL;
	if (tmp)
	{
		free(tmp[0]);
		free(tmp[1]);
	}
	free(tmp);
	return (ajout);
}

void	ft_def_env(char **base)
{
	int		i;
	t_liste	*ajout;

	i = 2;
	while (base[i])
	{
		ajout = ft_ajout_liste(base[i]);
		ft_lstaddend(&g_env, ajout);
		i++;
	}
}

void	ft_stockage_env(char *nom, char *valeur)
{
	char	*tmp;
	t_liste	*tmp2;

	tmp = ft_strjoin("$", nom);
	tmp2 = ft_cherche_env(tmp);
	free(tmp);
	if (tmp2 == NULL)
	{
		tmp = ft_strjoin(nom, "=");
		tmp = ft_strjoinfree(tmp, valeur, 1);
		ft_lstaddend(&g_env, ft_ajout_liste(tmp));
		free(tmp);
	}
	else
	{
		free(tmp2->valeur);
		tmp2->valeur = ft_strdup(valeur);
	}
}

int		ft_ajout_env(char **cmd)
{
	int		i;

	i = 0;
	if (cmd && cmd[0] && cmd[1] && cmd[2] && !cmd[3])
	{
		while (cmd[1][i])
			if (ft_isupper(cmd[1][i++]) == 0)
			{
				i = 0;
				break ;
			}
		if (i == 0)
		{
			free_tabtab(cmd);
			cmd = NULL;
			return (ft_ajout_env(cmd));
		}
		ft_stockage_env(cmd[1], cmd[2]);
		free_tabtab(cmd);
		return (1);
	}
	else
		ft_putstr("\033[01mUtilisation: setenv [NOM] [valeur]\033[00m\n");
	return (1);
}
