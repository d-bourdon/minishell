/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islink.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbourdon <dbourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 15:09:32 by dbourdon          #+#    #+#             */
/*   Updated: 2016/09/30 18:44:23 by dbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_islink(const char *path)
{
	struct stat	stats;
	int			tmp;

	tmp = 0;
	if (ft_strcmp(path, "../") == 0 || ft_strcmp(path, "./") == 0)
		return (0);
	if (lstat(path, &stats) == -1)
		return (0);
	tmp = S_ISLNK(stats.st_mode);
	if (tmp == 0)
		return (0);
	else
		return (1);
}
