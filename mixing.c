/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraivio <jraivio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:04:19 by jraivio           #+#    #+#             */
/*   Updated: 2022/05/26 15:23:15 by jraivio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisynth.h"

size_t	add_note(t_note	note, t_instrument instrument, t_song *song, 
		size_t track_i)
{
	t_wavetable	wavetable = wave_functions[instrument](note);

	for (size_t i = 0; i < note.duration; i++)
	{
		if (track_i > song->size)
		{
			song->size *= 2;
			song->master = realloc(song->master, song->size * sizeof(song->master));
			memset(song->master + (song->size / 2), 0, song->size / 2);
			if (song->master == NULL)
				exit(1);
		}
		song->master[track_i].sample += wavetable.samples[wavetable.size % i] * GAIN;
		song->master[track_i].instrument_count++;
		track_i++;
	}
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
