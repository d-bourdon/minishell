/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbourdon <dbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 17:06:26 by dbourdon          #+#    #+#             */
/*   Updated: 2016/09/30 18:38:02 by dbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_spe_cd(char **spe, char **path)
{
	if (*spe[0] == '~')
	{
		if (ft_cherche_env("$HOME") == NULL)
			ft_putstr("\033[01mcd:\033[31m Aucun $HOME défini.\033[00m");
		else
		{
			*spe = ft_strsubfree(*spe, 1, ft_strlen(*spe));
			*spe = ft_strjoinfree(ft_cherche_env("$HOME")->valeur, *spe, 2);
			return (0);
		}
		free_tabtab(path);
		return (1);
	}
	if (ft_strcmp(*spe, "-") == 0)
	{
		chdir(ft_cherche_env("$OLDPWD")->valeur);
		ft_stockage_env("----tmp", ft_cherche_env("$PWD")->valeur);
		ft_stockage_env("PWD", ft_cherche_env("$OLDPWD")->valeur);
		ft_stockage_env("OLDPWD", ft_cherche_env("$----tmp")->valeur);
		ft_suppr_env("----tmp");
		free_tabtab(path);
		return (1);
	}
	return (0);
}

static char	*ft_cd_lien2(char *tmp, char *path, char *tmp3)
{
	char	tmp2[500];

	tmp = ft_strsub(path, 0, ft_strlen(path) - ft_strlen(tmp3));
	if (tmp == NULL)
	{
		free(tmp);
		tmp = ft_strdup("./");
	}
	chdir(tmp);
	if (getcwd(tmp2, 500) == NULL)
		ft_erreur("Récuperation de PWD", 0);
	free(tmp);
	tmp = ft_strdup(tmp2);
	if (ft_strcmp(tmp, "/") == 0)
	{
		free(tmp);
		tmp = ft_strnew(0);
	}
	chdir(tmp3);
	if (tmp3[0] != '/')
		tmp = ft_strjoinfree(tmp, "/", 1);
	tmp = ft_strjoinfree(tmp, tmp3, 1);
	return (tmp);
}

int			ft_cd_lien(char *path, char **tpath)
{
	char	*tmp;
	char	*tmp3;

	tmp = NULL;
	if (ft_spe_cd(&tpath[1], tpath) == 1)
		return (1);
	if (ft_islink(path) == 0)
		return (0);
	tmp3 = ft_strrchr(path, '/');
	if (tmp3 == NULL)
		tmp3 = path;
	tmp = ft_cd_lien2(tmp, path, tmp3);
	ft_stockage_env("OLDPWD", ft_cherche_env("$PWD")->valeur);
	ft_stockage_env("PWD", tmp);
	free(tmp);
	free_tabtab(tpath);
	return (1);
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

int			ft_cd_option(char **path)
{
	char	tmp[500];

	if (ft_strcmp(path[1], "-L") == 0)
		if (ft_cd_lien(path[2], path) == 1)
			return (1);
	if (ft_spe_cd(&path[2], path) == 1)
		return (1);
	if (chdir(path[2]) == -1)
		check_existe(path[2], 0);
	else
	{
		if (getcwd(tmp, 500) == NULL)
			ft_erreur("Récuperation de PWD", 0);
		ft_stockage_env("OLDPWD", ft_cherche_env("$PWD")->valeur);
		ft_stockage_env("PWD", tmp);
	}
	free_tabtab(path);
	return (1);
}
