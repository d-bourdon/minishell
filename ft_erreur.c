/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_erreur.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbourdon <dbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 17:03:35 by dbourdon          #+#    #+#             */
/*   Updated: 2016/10/08 16:35:58 by dbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_erreur(char *str, int mode)
{
	if (mode == 0)
	{
		ft_putstr("\033[31mMinishell - Erreur\033[00m: ");
		ft_putstr(str);
		ft_putchar('\n');
		exit(1);
	}
	if (mode == 1)
	{
		ft_putstr("\033[31mMinishell - Commande inconnue\033[00m: ");
		ft_putstr(str);
		ft_putchar('\n');
		exit(1);
	}
	if (mode == 2)
	{
		ft_putstr("\033[31mEnv - La variable \033[00m");
		ft_putstr(str);
		ft_putstr("\033[31m n'existe pas.\n\033[00m");
		return ;
	}
	str = NULL;
}
