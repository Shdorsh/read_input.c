/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorsh <shdorsh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 02:46:33 by shdorsh           #+#    #+#             */
/*   Updated: 2024/12/29 14:53:45 by shdorsh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_input.h"

static int	string(char **c, long l)
{
	*c = (char *)malloc(sizeof (char) * (l + 1));
	(*c)[l] = 0;
	return (*c != (void *)0);
}

unsigned long	char_size(char *string)
{
	unsigned long	l;

	l = 0;
	while (string[l])
		l++;
	return (l);
}

static void	append_string(char **result, char **added)
{
	long	l_old;
	long	l_new;
	char	*fused_capture;

	l_old = char_size(*result);
	l_new = char_size(*added);
	if (!string(&fused_capture, l_new + l_old + 1))
		return ;
	l_old = 0;
	while ((*result)[l_old])
	{
		fused_capture[l_old] = (*result)[l_old];
		l_old++;
	}
	l_new = 0;
	while ((*added)[l_new])
	{
		fused_capture[l_new + l_old] = (*added)[l_new];
		l_new++;
	}
	fused_capture[l_old + l_new - 1] = 0;
	free(*result);
	*result = fused_capture;
}

void	read_loop(char **fused, char **expand)
{
	long	l;

	l = read(STDIN_FILENO, *expand, READLENGTH);
	while (l == READLENGTH)
	{
		append_string(fused, expand);
		l = read(STDIN_FILENO, *expand, READLENGTH);
	}
	while (l < READLENGTH)
	{
		(*expand)[l] = 0;
		l++;
	}
	append_string(fused, expand);
}

char	*read_input(char *query)
{
	char	*fused;
	char	*expand;
	int		i;

	if (!string(&fused, 1))
		return ((void *)0);
	if (!string(&expand, READLENGTH + 1))
	{
		free(fused);
		return ((void *)0);
	}
	fused[0] = 0;
	expand[READLENGTH] = 0;
	if (query)
	{
		i = 0;
		while (query[i])
			i++;
		write(STDOUT_FILENO, query, i);
	}
	read_loop(&fused, &expand);
	free(expand);
	return (fused);
}
