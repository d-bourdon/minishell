/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbourdon <dbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 14:22:51 by dbourdon          #+#    #+#             */
/*   Updated: 2016/09/25 15:09:07 by dbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sighandler(int signum)
{
	signum++;
	write(0, "\0\r", 2);
	ft_putstr("\n\033[1;32m$\033[33m--> \033[00m");
}

static void	ft_affichage_help(void)
{
	ft_putstr("\033[1;34m*************************************************\n");
	ft_putstr("*    ___  ____       _ _____ _          _ _     *\n");
	ft_putstr("*    |  \\/  (_)     (_)  ___| |        | | |    *\n");
	ft_putstr("*    | .  . |_ _ __  _\\ `--.| |__   ___| | |    *\n");
	ft_putstr("*    | |\\/| | | '_ \\| |`--. \\ '_ \\ / _ \\ | |    *\n");
	ft_putstr("*    | |  | | | | | | /\\__/ / | | |  __/ | |    *\n");
	ft_putstr("*    \\_|  |_/_|_| |_|_\\____/|_| |_|\\___|_|_|    *\n");
	ft_putstr("*                                               *\n");
	ft_putstr("*************************************************\033[00m\n\n");
	ft_putstr("\033[01m-------------- Commandes spécifique -------------\n");
	ft_putstr("- env : Affiche les variables d'environement.\n\n");
	ft_putstr("- setenv [NOM] [valeur] : défini une valeur \n");
	ft_putstr("		d'environement ou en en créer une nouvelle.\n\n");
	ft_putstr("- unsetenv [NOM] : supprime une variable \n");
	ft_putstr("		d'environement\n\n");
	ft_putstr("- cd [-L|-P] [dossier| - | ~] : Change de dossier :\n");
	ft_putstr("	- -> reviens à l'ancien dossier.\n");
	ft_putstr("	~ -> renvoie au home.\n");
	ft_putstr("- exit [nb| 666] : quitte le minishell\n");
	ft_putstr("	666 -> éxécute une boucle sans fin | debug\n");
	ft_putstr("-------------------------------------------------\n\033[00m");
	ft_putstr("v 0.0.1 - 2016 dbourdon\n");
}

int			main(void)
{
	char		**str;
	int			i;
	extern char	**environ;
	t_liste		*tmp;

	ft_def_env(environ);
	ft_affichage_help();
	while (42)
	{
		str = (char**)malloc(sizeof(char*) * 1);
		ft_putstr("\n\033[1;34m");
		ft_putstr(ft_cherche_env("$PWD")->valeur);
		ft_putstr("\n\033[1;32m$\033[33m--> \033[00m");
		signal(SIGINT, sighandler);
		signal(SIGQUIT, sighandler);
		i = get_next_line(0, str);
		if (str[0][0] == '\0')
			ft_affichage_help();
		if (str[0][0] != '\0' && (tmp = ft_cherche_env(str[0])) != NULL)
			ft_affichage_un_env(tmp);
		if (str[0][0] != '\0')
			split_commande(str[0], str);
	}
	return (1);
}
