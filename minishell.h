/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbourdon <dbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 15:13:30 by dbourdon          #+#    #+#             */
/*   Updated: 2016/10/08 15:27:59 by dbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct		s_liste
{
	char			*nom;
	char			*valeur;
	struct s_liste	*next;
}					t_liste;

t_liste				*g_env;

void				free_tabtab(char **tab);
void				free_env(void);
int					ft_exit(char **cmd);
void				sighandler(int signum);
int					ft_cd(char **path);

void				ft_erreur(char *str, int mode);

int					exec_cmd(char **cmd);
char				*split_commande(char *str, char **strbase);
int					ft_cherche_cmd(char	**cmd);

char				**ft_retour_env(void);
void				ft_redef_env(char **tab);
t_liste				*ft_cherche_env(char *nom);
void				ft_lstaddend(t_liste **liste, t_liste *ajout);
t_liste				*ft_ajout_liste(char *base);
void				ft_def_env(char **base);
int					ft_affichage_env(void);
void				ft_affichage_un_env(t_liste *un);
int					ft_ajout_env(char **cmd);
void				ft_suppr_env(char *nom);
void				ft_stockage_env(char *nom, char *valeur);
int					ft_retrait_env(char **cmd);

int					ft_islink(const char *path);
int					ft_cd_option(char **path);
int					ft_cd_lien(char *path, char **tpath);

#endif
