/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wavefunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:03:07 by carlnysten        #+#    #+#             */
/*   Updated: 2022/05/25 18:05:30 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <math.h>
#include "minisynth.h"

#define TEMPO 110

static const float pitch[] = {
	0.0f,
	220.0f,
	246.94f,
	261.63f,
	293.66f,
	329.63f,
	349.23f,
	392.00f
};

int	sine_wave(SDL_AudioDeviceID audio_device, t_note note)
{
	float	x = 0.0f;
	int16_t	sample = 0;

	for (int i = 0; i < FREQ * (TEMPO / 60) * note.duration; i++)
	{
		x += 1.0f;
		sample = sin((x / (float) FREQ) * 2.0f * M_PI * pitch[note.pitch]) * GAIN;
		SDL_QueueAudio(audio_device, &sample, SAMPLE_SIZE);
	}
	return (0);
}

int	saw_wave(SDL_AudioDeviceID audio_device, t_note note)
{
	float	x = 0.0;
	int16_t	sample = 0;

	for (int i = 0; i < note.duration; i++)
	{
		x += 0.010f;
		sample = sin(x) * GAIN;
		SDL_QueueAudio(audio_device, &sample, SAMPLE_SIZE);
	}
	return (0);
}

int	square_wave(SDL_AudioDeviceID audio_device, t_note note)
{
	float	x = 0.0;
	int16_t	sample = 0;

	for (int i = 0; i < note.duration; i++)
	{
		x += 0.010f;
		sample = sin(x) * GAIN;
		SDL_QueueAudio(audio_device, &sample, SAMPLE_SIZE);
	}
	return (0);
}

int	tri_wave(SDL_AudioDeviceID audio_device, t_note note)
{
	float	x = 0.0;
	int16_t	sample = 0;

	for (int i = 0; i < note.duration; i++)
	{
		x += 0.010f;
		sample = sin(x) * GAIN;
		SDL_QueueAudio(audio_device, &sample, SAMPLE_SIZE);
	}
	return (0);
}
