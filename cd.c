/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbourdon <dbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 14:19:46 by dbourdon          #+#    #+#             */
/*   Updated: 2016/10/02 13:24:33 by dbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_gohome(void)
{
	if (chdir(ft_cherche_env("$HOME")->valeur) == -1)
		ft_putstr("\033[01mcd:\033[31m Aucun $HOME défini.\033[00m");
	else
	{
		ft_stockage_env("OLDPWD", ft_cherche_env("$PWD")->valeur);
		ft_stockage_env("PWD", ft_cherche_env("$HOME")->valeur);
	}
}

static void	check_existe(char *path, int mode)
{
	if (mode == 0)
	{
		if (access(path, F_OK) == 0)
			ft_putstr("\033[01mcd:\033[31m Chemin interdit : \033[00m");
		else
			ft_putstr("\033[01mcd:\033[31m Chemin inexistant : \033[00m");
		ft_putstr(path);
	}
	else
	{
		ft_putstr("\033[31mCommande invalide\033[00m: cd [-L|-P] [\033[01mdo");
		ft_putstr("ssier\033[00m | \033[01m..\033[00m | \033[01m/\033[00m ");
		ft_putstr("| \033[01m-\033[00m | \033[01m~\033[00m |  ]");
	}
}

int			ft_cd(char **path)
{
	char	tmp[500];

	if (path[0] && !path[1])
		ft_gohome();
	else if (ft_strcmp(path[1], "-L") == 0 || ft_strcmp(path[1], "-P") == 0)
		return (ft_cd_option(path));
	else if (path[0] && path[1] && !path[2])
	{
		if (ft_cd_lien(path[1], path) == 1)
			return (1);
		else if (chdir(path[1]) == -1)
			check_existe(path[1], 0);
		else
		{
			if (getcwd(tmp, 500) == NULL)
				ft_erreur("Récuperation de PWD", 0);
			ft_stockage_env("OLDPWD", ft_cherche_env("$PWD")->valeur);
			ft_stockage_env("PWD", tmp);
		}
	}
	else
		check_existe(path[1], 1);
	free_tabtab(path);
	return (1);
}
