/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboivin <tboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:19:52 by tboivin           #+#    #+#             */
/*   Updated: 2017/02/17 07:33:50 by tboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_opt	*set_opt(int av, char **ac)
{
	t_opt *s;

	if (!(s = (t_opt *)malloc(sizeof(t_opt))))
		return (NULL);
	s->i = 1;
	s->av = av;
	s->ac = ac;
	s->path = NULL;
	s->test = NULL;
	s->s = 0;
	s->j = 0;
	s->r = 0;
	s->o = 0;
	s->n = 0;
	s->k = 1;
	s->ac_i = 0;
	return (s);
}
