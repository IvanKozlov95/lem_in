/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 22:08:08 by mtan              #+#    #+#             */
/*   Updated: 2018/04/03 22:08:13 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

void	parse_comment(char *line, int *i, t_vertex *v, int *prev)
{
	if (line[1] == '#' && (ft_strstr(line, "start") || ft_strstr(line, "end")))
	{
		*prev = 1;
		if (ft_strstr(line, "start"))
			v[*i].type = START;
		else if (ft_strstr(line, "end"))
			v[*i].type = END;
	}
	(*i)--;
}

void	put_line(char *line)
{
	ft_putendl(line);
	free(line);
}
