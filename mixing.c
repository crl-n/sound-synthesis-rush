/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraivio <jraivio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:04:19 by jraivio           #+#    #+#             */
/*   Updated: 2022/05/27 20:32:44 by jraivio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisynth.h"

size_t	add_note(t_note	note, t_instrument instrument, t_song *song, 
		size_t track_i)
{
	t_wavetable	wavetable = wave_functions[instrument](note);

	for (size_t i = 0; i < note.duration; i++)
	{
		if (track_i >= song->size)
		{
			t_track *temp = malloc(sizeof(t_track) * (song->size * 2));
			if (!temp)
				exit(1);
			bzero(temp, sizeof(t_track) * (song->size * 2));
			memcpy(temp, song->master, sizeof(t_track) * song->size);
			song->size *= 2;
			free(song->master);
			song->master = temp; 
		}
		if (note.pitch > 1 && note.pitch < 40000)
		{
			song->master[track_i].sample += wavetable.samples[i % wavetable.size];
			song->master[track_i].instrument_count++;
		}
		track_i++;
	}
	if (wavetable.samples)
		free(wavetable.samples);
	return (track_i);
}

void	mix_song_volume(t_song *song)
{
	for (size_t i = 0; i < song->size; i++)
	{
		if (song->master[i].instrument_count > 1)
			song->master[i].sample /= song->master[i].instrument_count;
	}
}
