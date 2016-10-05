/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbourdon <dbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 14:38:34 by dbourdon          #+#    #+#             */
/*   Updated: 2016/06/16 14:58:58 by dbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstaddend(t_liste **liste, t_liste *ajout)
{
	t_liste	*tmp;

	tmp = *liste;
	if (*liste == NULL)
	{
		*liste = ajout;
		return ;
	}
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		if (ajout != NULL)
			tmp->next = ajout;
	}
}
