/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dec_commande.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbourdon <dbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 16:13:31 by dbourdon          #+#    #+#             */
/*   Updated: 2016/10/08 15:37:54 by dbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd_fils(char **path, char **cmd, char **envtab)
{
	int		i;
	int		null;

	i = 0;
	null = 1;
	while (path && path[i] && null == 1)
	{
		null = 0;
		path[i] = ft_strjoinfree(path[i], "/", 1);
		if (execve(ft_strjoin(path[i], cmd[0]), cmd, envtab) == -1)
			null = 1;
		i++;
	}
	execve(cmd[0], cmd, envtab);
	ft_erreur(cmd[0], 1);
}

int			exec_cmd(char **cmd)
{
	char		**path;
	char		**envtab;
	pid_t		pid;
	int			status;
	t_liste		*test;
	
	path = NULL;
	test = ft_cherche_env("$PATH");
	if (test)
		path = ft_strsplit(test->valeur, ':');
	envtab = ft_retour_env();
	pid = fork();
	if (pid > 0)
	{
		wait(&status);
		free_tabtab(path);
		free_tabtab(envtab);
		free_tabtab(cmd);
		return (0);
	}
	if (pid == 0)
		exec_cmd_fils(path, cmd, envtab);
	return (1);
}

int			ft_cherche_cmd(char **cmd)
{
	if (ft_strcmp(cmd[0], "env") == 0 && !cmd[1])
	{
		free_tabtab(cmd);
		return (ft_affichage_env());
	}
	if (ft_strcmp(cmd[0], "setenv") == 0)
		return (ft_ajout_env(cmd));
	if (ft_strcmp(cmd[0], "unsetenv") == 0)
		return (ft_retrait_env(cmd));
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (ft_cd(cmd));
	return (0);
}

static void	cmd_env(char ***split)
{
	t_liste	*tmp;
	int		i;

	i = 0;
	while ((*split)[i])
	{
		if ((tmp = ft_cherche_env((*split)[i])) != NULL)
		{
			free((*split)[i]);
			(*split)[i] = ft_strdup(tmp->valeur);
		}
		i++;
	}
}

char		*split_commande(char *str, char **strbase)
{
	char	**split;

	split = ft_strsplitw(str);
	free(str);
	free(strbase);
	if (split[0] == NULL)
	{
		free_tabtab(split);
		return (NULL);
	}
	cmd_env(&split);
	if (ft_exit(split) == 1)
		return (NULL);
	if (!split[0])
		return (NULL);
	if (ft_cherche_cmd(split))
		return (NULL);
	if (exec_cmd(split) == 0)
		return (NULL);
	return (NULL);
}
