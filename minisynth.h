/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisynth.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:14:58 by cnysten           #+#    #+#             */
/*   Updated: 2022/05/27 20:21:46 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISYNTH_H
# define MINISYNTH_H

# include <SDL.h>
# include <string.h>

# define GAIN 20000
# define SAMPLE_SIZE 2
# define SAMPLE_RATE 44100

typedef enum e_instrument
{
	sine,
	saw,
	square,
	triangle
}	t_instrument;

typedef enum e_pitch
{
	r,
	a,
	b,
	c,
	d,
	e,
	f,
	g
}	t_pitch;

typedef struct	s_note
{
	float	pitch;
	size_t	duration;
}	t_note;

typedef struct	s_track
{
	float		sample;
	int8_t		instrument_count;
}	t_track;

typedef struct	s_song
{
	t_track	*master;
	size_t	size;
	size_t	length;
	int		tempo;
}	t_song;

typedef struct	s_wavetable
{
	float	*samples;
	size_t	size;
}	t_wavetable;

typedef	t_wavetable (*t_wavefunc)(t_note note);

t_wavetable	sine_wave(t_note note);
t_wavetable	saw_wave(t_note note);
t_wavetable	square_wave(t_note note);
t_wavetable	tri_wave(t_note note);
t_song		parse(char *filename);
size_t		add_note(t_note	note, t_instrument instrument, t_song *song, 
					size_t track_i);
void		mix_song_volume(t_song *song);

static const t_wavefunc wave_functions[] = {
	sine_wave,
	saw_wave,
	tri_wave,
	square_wave
};

#endif
