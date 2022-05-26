/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraivio <jraivio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:04:19 by jraivio           #+#    #+#             */
/*   Updated: 2022/05/26 14:45:18 by jraivio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisynth.h"

size_t	add_note(t_note	note, t_instrument instrument, t_song *song, 
		size_t track_i)
{
	t_wavetable	wavetable = wave_functions[instrument](note);

	for (size_t i = 0; i < note.duration; i++;)
	{
		if (track_i > song->size)
		{
			song->size *= 2;
			song->master = realloc(song->master, size * sizeof(song->master));
			song->instrument_count = realloc(song->master, 
										size * sizeof(song->instrument_count));
			if (song->master == NULL || song->instrument_count = NULL)
				exit(1);
		}
		song->master[track_i] += wavetable.samples[wavetable.size % i] * GAIN;
		song->instrument_count[track_i]++;
		track_i++;
	}
	return (track_i);
}

void	mix_song_volume(t_song *song)
{
	for (size_t i = 0; i < song->size; i++;)
	{
		if (song->instrument_count[i] > 1)
			song->master[i] /= song->instrument_count[i];
	}
}
