/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wavefunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:03:07 by carlnysten        #+#    #+#             */
/*   Updated: 2022/05/25 17:01:35 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <math.h>
#include "minisynth.h"

#define TEMPO 110

int	sine_wave(SDL_AudioDeviceID audio_device, int duration)
{
	float	x = 0.0;
	int16_t	sample = 0;

	for (int i = 0; i < FREQ * (TEMPO / 60) * duration; i++)
	{
		x += 0.010f;
		sample = sin(x) * GAIN;
		SDL_QueueAudio(audio_device, &sample, SAMPLE_SIZE);
	}
	return (0);
}

int	saw_wave(SDL_AudioDeviceID audio_device, int duration)
{
	float	x = 0.0;
	int16_t	sample = 0;

	for (int i = 0; i < duration; i++)
	{
		x += 0.010f;
		sample = sin(x) * GAIN;
		SDL_QueueAudio(audio_device, &sample, SAMPLE_SIZE);
	}
	return (0);
}

int	square_wave(SDL_AudioDeviceID audio_device, int duration)
{
	float	x = 0.0;
	int16_t	sample = 0;

	for (int i = 0; i < duration; i++)
	{
		x += 0.010f;
		sample = sin(x) * GAIN;
		SDL_QueueAudio(audio_device, &sample, SAMPLE_SIZE);
	}
	return (0);
}

int	tri_wave(SDL_AudioDeviceID audio_device, int duration)
{
	float	x = 0.0;
	int16_t	sample = 0;

	for (int i = 0; i < duration; i++)
	{
		x += 0.010f;
		sample = sin(x) * GAIN;
		SDL_QueueAudio(audio_device, &sample, SAMPLE_SIZE);
	}
	return (0);
}
