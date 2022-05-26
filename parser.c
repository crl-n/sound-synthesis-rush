/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:36:24 by carlnysten        #+#    #+#             */
/*   Updated: 2022/05/26 14:55:31 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "minisynth.h"

t_song	parse(char *filename)
{
	t_song	song;
	FILE	*file;
	size_t	sample_index = 0;

	bzero(&song, sizeof (t_song));
	(void) sample_index;

	if ((file = fopen(filename, "r")))
	{
		size_t	linesize = 0;
		char	*line = NULL;
		ssize_t	bytes_read = 0;

		// Get tempo
		while ((bytes_read = getline(&line, &linesize, file)))
		{
			if (strncmp(line, "tempo", 5) == 0)
			{
				song.tempo = atoi(line + 5);
				free(line);
				line = NULL;
				break ;
			}
			free(line);
			line = NULL;
		}
		
		// Get track instruments
		int	n_tracks = 1;
		while ((bytes_read = getline(&line, &linesize, file)))
		{
			if (strncmp(line, "tracks", 6) == 0)
			{
				// Count how many tracks
				for (int i = 0; line[i]; i++)
				{
					if (line[i] == ',')
						n_tracks++;
				}

				// Get instruments
				t_instrument	track_instruments[32] = {0};
				int				trackid = 1;
				char			*token = strtok(line, ",");
				while (token != NULL)
				{
					if (!strcmp(line, "sine"))
						track_instruments[trackid++] = sine;
					else if (!strcmp(line, "saw"))
						track_instruments[trackid++] = saw;
					else if (!strcmp(line, "triangle"))
						track_instruments[trackid++] = triangle;
					else if (!strcmp(line, "square"))
						track_instruments[trackid++] = square;
					token = strtok(NULL, ",");
				}
				
				free(line);
				line = NULL;
				break ;
			}
			free(line);
			line = NULL;
		}

		// Get track notes
		while ((bytes_read = getline(&line, &linesize, file)))
		{
			if (isdigit(line[0]) && line[1] == ':')
			{
				char	*token = strtok(line, " ");
				token = strtok(NULL, " ");
				while (token != NULL)
				{
					//printf("%s ", token);

					/*
					printf("%c ", token[0]);
					if (isdigit(token[2]))
						printf("%d ", atoi(token + 2));
					else
						printf("%d ", atoi(token + 3));
					printf("%f ", atof(strchr(token, '/') + 1));
					*/

					token = strtok(NULL, " ");
				}
				free(line);
				line = NULL;
				break ;
			}
			free(line);
			line = NULL;
		}
		
	}
	else
	{

	}
	return (song);
}

