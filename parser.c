/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:36:24 by carlnysten        #+#    #+#             */
/*   Updated: 2022/05/27 13:42:58 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "minisynth.h"

static const float pitch_table[] = {
	30.87f,
	32.70f,
	34.65f,
	36.71f,
	38.89f,
	41.20f,
	43.65f,
	46.25f,
	49.00f,
	51.91f,
	55.00f,
	58.27f,
	61.74f
};

t_note	get_note(char	*token, int tempo)
{
	static	int		octave = 4;
	static	float	beat_length = 1.0f;
	int	note_i = 0;
	t_note note;

	note.pitch = -1;
	switch (token[0])
	{
		case 'c':
			note_i = 1;
			break;
		case 'd':
			note_i = 3;
			break;
		case 'e':
			note_i = 5;
			break;
		case 'f':
			note_i = 6;
			break;
		case 'g':
			note_i = 8;
			break;
		case 'a':
			note_i = 10;
			break;
		case 'b':
			note_i = 12;
			break;
		case 'r':
			note_i = -1;
			break;
		default:
			break;
	}
	token++;
	while (token)
		{
			if (token[0] == '#' || token[0] == 'b')
				note_i += (token[0] == 'b' ? -1 : 1);
			else if (isdigit(token[0]))
				octave = atoi(token);
			else if (token[0] == '/')
			{
				token++;
				beat_length = atof(token);
				break;
			}
			token++;
		}
	note.duration = (size_t)(((float)SAMPLE_RATE * (60 / (float)tempo)) * beat_length);
	if (note_i < 0)
		return(note);
	note.pitch = (pitch_table[note_i] / 2);
	for (int i = 0; i < octave; i++)
		note.pitch *= 2;
	return (note);
}

t_song	parse(char *filename)
{
	t_song	song;
	FILE	*file;
	size_t	sample_index = 0;

	//bzero(&song, sizeof (t_song));
	song.size = SAMPLE_RATE;
	song.master = malloc(sizeof(song.master) * song.size);
	if (!song.master)
		exit(1);
	bzero(song.master, song.size);

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
		int	trackid = 1;
		t_instrument	track_instruments[32] = {0};
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
		trackid = 1;
		while ((bytes_read = getline(&line, &linesize, file)))
		{
			if (isdigit(line[0]) && line[1] == ':')
			{
				char	*token = strtok(line, " ");
				token = strtok(NULL, " ");
				while (token != NULL)
				{
					sample_index = add_note(
							get_note(token, song.tempo), track_instruments[trackid],
							&song,
							sample_index
					);
					token = strtok(NULL, " ");
				}
				free(line);
				line = NULL;
				sample_index = 0;
				trackid++;
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

