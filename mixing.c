/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraivio <jraivio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:04:19 by jraivio           #+#    #+#             */
/*   Updated: 2022/05/27 23:02:01 by jraivio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisynth.h"

size_t	add_note(t_note	note, t_instrument instrument, t_song *song, 
		size_t track_i)
{
	t_wavetable	wavetable = wave_functions[instrument](note);
	float		amp_mod;
	size_t		attack;
	size_t		decay;
	size_t		release;
	float		sustain;
	int			envelope_phase;
	float		vol;

	vol = 1.0f;
	amp_mod = 0.0f;
	sustain = 0.9f;
	attack = 2000;
	decay = 1000;
	release = 2000;
	envelope_phase = 0;
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
			song->master[track_i].sample += wavetable.samples[i % wavetable.size] * amp_mod * vol;
			song->master[track_i].instrument_count++;
		}
		switch (envelope_phase)
		{
			case 0:
				amp_mod = 1.000f * ((float)i / (float)attack); 
				if (i >= attack)
				{
					envelope_phase++;
					break;
				}
				break;
			case 1:
				amp_mod -= (1.0f - sustain) / decay;
				if (i - attack > decay)
					envelope_phase++;
				break;
			case 2:
				if (note.duration - i < release)
					envelope_phase++;
				break;
			case 3:
				amp_mod = sustain * ((float)(note.duration - i - 1) / (float)release);
				break;
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
