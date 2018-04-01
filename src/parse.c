/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 14:11:16 by mtan              #+#    #+#             */
/*   Updated: 2018/03/31 14:11:25 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

void	parse_ants(t_ant **ants, int *ant_count)
{
	char	*line;
	int		i;

	if (!get_next_line(0, &line))
		error("Error: No File");
	*ant_count = ft_atoi(line);
	if (!ft_isdigit_str(line) || *ant_count <= 0)
		error("Error: No Ants");
	*ants = malloc(sizeof(t_ant) * (*ant_count));
	i = -1;
	while (++i < *ant_count)
	{
		(*ants)[i].progress = 0;
		(*ants)[i].path = NULL;
		(*ants)[i].number = *ant_count;
	}
	ft_putendl(line);
	free(line);
}

char	*parse_vertex(t_vertex *v, int *i)
{
	char		*line;
	int			ends;

	*i = 0;
	ends = 0;
	while (get_next_line(0, &line))
	{
		if (ft_strchr(line, '-'))
			break ;
		else if (line[0] == '#')
			parse_comment(line, &ends, i, v);
		else
			store_vertex(v, line, *i);
		(*i)++;
		ft_putendl(line);
		free(line);
	}
	if (!*i)
		error("Error: No rooms");
	if (ends < 2)
		error("Error: No Start or End");
	return (line);
}

void	parse_links(t_graph *g, t_vertex *v, char *line)
{
	if (line == NULL)
		error("Error: No Links");
	store_link(g, v, line);
	while (get_next_line(0, &line))
		store_link(g, v, line);
}

void	parse_input(t_ant **ants, int *ant_count, t_list **p, t_graph *g)
{
	t_vertex	tmp[42];
	char		*line;
	int			i;

	parse_ants(ants, ant_count);
	line = parse_vertex(tmp, &i);
	g->V = i;
	g->nodes = malloc(sizeof(t_vertex) * g->V);
	i = -1;
	while (++i < g->V)
	{
		g->nodes[i].number = i;
		g->nodes[i].name = ft_strdup(tmp[i].name);
		g->nodes[i].type = tmp[i].type ? tmp[i].type : 0;
		g->nodes[i].children = NULL;
	}
	parse_links(g, tmp, line);
	i = -1;
	while (++i < g->V)
		free(tmp[i].name);
	*p = find_paths(*g, 2, 3);
}
