/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisynth.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:14:58 by cnysten           #+#    #+#             */
/*   Updated: 2022/05/25 17:21:27 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISYNTH_H
# define MINISYNTH_H

# include <SDL.h>

# define GAIN 5000
# define SAMPLE_SIZE 2
# define FREQ 44100

typedef	int (*t_wavefunc)(SDL_AudioDeviceID audio_device, int duration);

int	sine_wave(SDL_AudioDeviceID audio_device, int duration);
int	saw_wave(SDL_AudioDeviceID audio_device, int duration);
int	square_wave(SDL_AudioDeviceID audio_device, int duration);
int	tri_wave(SDL_AudioDeviceID audio_device, int duration);

static const t_wavefunc wave_functions[] = {
	sine_wave,
	saw_wave,
	square_wave,
	tri_wave
};

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
	t_pitch	pitch;
	int		alteration;
	int		octave;
	float	duration;
	float	current_duration;
}	t_note;

typedef struct	s_track
{
	t_instrument	instrument;
	t_note			*notes;
}	t_track;

typedef struct	s_song
{
	int		tempo;
	t_track	*tracks;
}	t_song;

#endif
