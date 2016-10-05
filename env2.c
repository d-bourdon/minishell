/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbourdon <dbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 13:45:09 by dbourdon          #+#    #+#             */
/*   Updated: 2016/09/24 14:41:36 by dbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_redef_env(char **tab)
{
	int		i;
	t_liste	*tmp;
	char	**tmp2;

	i = 0;
	while (tab[i])
	{
		tmp2 = ft_strsplit(tab[i], '=');
		tmp = ft_cherche_env(ft_strjoin("$", tmp2[0]));
		if (tmp != NULL)
		{
			free(tmp->valeur);
			tmp->valeur = ft_strdup(tmp2[1]);
		}
		else if (tmp2[0] != NULL)
			ft_lstaddend(&g_env, ft_ajout_liste(tab[i]));
		i++;
	}
}

static void	free_liste(t_liste *lst)
{
	free(lst->nom);
	free(lst->valeur);
	free(lst);
}

static void	suppr_cont_env(t_liste *tmp, t_liste *tmp2, char *nom)
{
	tmp = g_env;
	if (ft_strcmp(tmp->nom, nom) == 0)
	{
		tmp2 = tmp->next;
		free_liste(tmp);
		g_env = tmp2;
		return ;
	}
	while (tmp->next && ft_strcmp(tmp->next->nom, nom))
		tmp = tmp->next;
	if (tmp->next->next)
	{
		tmp2 = tmp->next->next;
		free_liste(tmp->next);
		tmp->next = tmp2;
	}
	else
	{
		free_liste(tmp->next);
		tmp->next = NULL;
	}
}

void		ft_suppr_env(char *nom)
{
	t_liste	*tmp;
	t_liste	*tmp2;
	char	*tmp3;

	tmp2 = NULL;
	tmp3 = ft_strjoin("$", nom);
	tmp = ft_cherche_env(tmp3);
	free(tmp3);
	if (tmp == NULL)
		return (ft_erreur(nom, 2));
	else
		suppr_cont_env(tmp, tmp2, nom);
	return ;
}

int			ft_retrait_env(char **cmd)
{
	int		i;

	i = 0;
	if (cmd[0] && cmd[1] && !cmd[2])
	{
		ft_suppr_env(cmd[1]);
		free_tabtab(cmd);
		return (1);
	}
	else
	{
		free_tabtab(cmd);
		ft_putstr("\033[01mUtilisation: unsetenv [NOM]\033[00m\n");
	}
	return (1);
}
