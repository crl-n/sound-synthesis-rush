/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wavefunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:03:07 by carlnysten        #+#    #+#             */
/*   Updated: 2022/05/26 12:10:40 by carlnysten       ###   ########.fr       */
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

	//printf("Sine\n");
	for (int i = 0; i < SAMPLE_RATE * (TEMPO / 60) * note.duration; i++)
	{
		x += 1.0f;
		sample = sin((x / (float) SAMPLE_RATE) * 2.0f * M_PI * pitch[note.pitch]) * GAIN;
		SDL_QueueAudio(audio_device, &sample, SAMPLE_SIZE);
	}
	return (0);
}

int	saw_wave(SDL_AudioDeviceID audio_device, t_note note)
{
	float	x = -0.01 * pitch[note.pitch] / 2;
	int16_t	sample = 0;

	//printf("Saw x %f \n", x);
	for (int i = 0; i < SAMPLE_RATE * (TEMPO / 60) * note.duration; i++)
	{
		if (i % (int) pitch[note.pitch] == 0)
			x = -0.01 * pitch[note.pitch] / 2;
		x += 0.01;
		sample = x * GAIN;
		SDL_QueueAudio(audio_device, &sample, SAMPLE_SIZE);
	}
	return (0);
}

int	tri_wave(SDL_AudioDeviceID audio_device, t_note note)
{
	float	x = 0.0;
	float	sine_value = 0.0f;
	int16_t	sample = 0;

	//printf("Tri\n");
	for (int i = 0; i < SAMPLE_RATE * (TEMPO / 60) * note.duration; i++)
	{
		sine_value = sin(((float) i / (float) SAMPLE_RATE) * 2.0f * M_PI * pitch[note.pitch]);
		x += ((sine_value < 0.0f) ? -0.01 : 0.01);
		sample = x * GAIN;
		SDL_QueueAudio(audio_device, &sample, SAMPLE_SIZE);
	}
	return (0);
}

int	square_wave(SDL_AudioDeviceID audio_device, t_note note)
{
	float	x = 0.0f;
	float	sine_value = 0.0f;
	int16_t	sample = 0;

	//printf("Square\n");
	for (int i = 0; i < SAMPLE_RATE * (TEMPO / 60) * note.duration; i++)
	{
		x += 1.0f;
		sine_value = sin((x / (float) SAMPLE_RATE) * 2.0f * M_PI * pitch[note.pitch]);
		sample = (sine_value < 0) ? GAIN : -GAIN;
		SDL_QueueAudio(audio_device, &sample, SAMPLE_SIZE);
	}
	return (0);
}
