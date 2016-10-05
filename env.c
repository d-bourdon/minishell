/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbourdon <dbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 17:51:11 by dbourdon          #+#    #+#             */
/*   Updated: 2016/09/20 18:18:22 by dbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_retour_env2(t_liste *tmp, char **out, int j)
{
	char	*tmp2;

	while (tmp)
	{
		tmp2 = ft_strnew(0);
		tmp2 = ft_strjoinfree(tmp2, tmp->nom, 1);
		tmp2 = ft_strjoinfree(tmp2, "=", 1);
		tmp2 = ft_strjoinfree(tmp2, tmp->valeur, 1);
		out[j++] = ft_strdup(tmp2);
		free(tmp2);
		tmp = tmp->next;
	}
	out[j] = NULL;
	return (out);
}

char		**ft_retour_env(void)
{
	t_liste	*tmp;
	char	**out;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = g_env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	out = (char **)malloc(sizeof(char*) * (i + 1));
	tmp = g_env;
	return (ft_retour_env2(tmp, out, j));
}

int			ft_affichage_env(void)
{
	t_liste		*tmp;

	tmp = g_env;
	while (tmp)
	{
		ft_putstr(tmp->nom);
		ft_putchar('=');
		ft_putstr(tmp->valeur);
		ft_putchar('\n');
		tmp = tmp->next;
	}
	return (1);
}

void		ft_affichage_un_env(t_liste *un)
{
	ft_putstr(un->nom);
	ft_putchar('=');
	ft_putstr(un->valeur);
	ft_putchar('\n');
}

t_liste		*ft_cherche_env(char *nom)
{
	t_liste	*tmp;
	char	*tmpchar;

	tmp = g_env;
	while (tmp)
	{
		tmpchar = ft_strjoin("$", tmp->nom);
		if (ft_strcmp(nom, tmpchar) == 0)
		{
			free(tmpchar);
			return (tmp);
		}
		free(tmpchar);
		tmp = tmp->next;
	}
	tmp = NULL;
	return (tmp);
}
