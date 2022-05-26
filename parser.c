/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:36:24 by carlnysten        #+#    #+#             */
/*   Updated: 2022/05/26 13:03:52 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "minisynth.h"

t_song	parse(char *filename)
{
	t_song	song;

	(void) filename;
	bzero(&song, sizeof (t_song));

	/*
	FILE	*file;
	size_t	sample_index = 0;
	if (file = fopen(filename, "r")
	{
		size_t	linesize = 0;
		char	*line = NULL;

		while (bytes_read = getline(line, &linesize, file))
		{
			
		}
		

	}
	else
	{

	}
	*/
	return (song);
}

