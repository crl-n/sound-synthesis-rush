/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wavefunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:03:07 by carlnysten        #+#    #+#             */
/*   Updated: 2022/05/27 20:49:41 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <math.h>
#include "minisynth.h"

t_wavetable	sine_wave(t_note note)
{
	if (note.pitch < 0.f)
		return((t_wavetable){.samples = NULL, .size = 0});
	float	x = 0.0f;
	t_wavetable wavetable;

	wavetable.size = SAMPLE_RATE / note.pitch;
	wavetable.samples = malloc(sizeof(wavetable.samples) * wavetable.size);
	if (wavetable.samples == NULL)
	{
		exit(1);
	}
	for (size_t i = 0; i < wavetable.size; i++)
	{
		x += 1.0f;
		wavetable.samples[i] = sin((x / (float)SAMPLE_RATE) * 2.0f * M_PI * note.pitch);
	}
	return (wavetable);
}

t_wavetable	saw_wave(t_note note)
{
	if (note.pitch == 0.f)
		return((t_wavetable){.samples = NULL, .size = 0});
	float	x = -0.01 * note.pitch / 2;
	t_wavetable wavetable;

	wavetable.size = SAMPLE_RATE / note.pitch;
	wavetable.samples = malloc(sizeof(wavetable.samples) * wavetable.size);
	if (wavetable.samples == NULL)
	{
		exit(1);
	}
	for (size_t i = 0; i < wavetable.size; i++)
	{
		if (i % (int) note.pitch == 0)
			x = -0.01 * note.pitch / 2;
		x += 0.01;
		wavetable.samples[i] = x * GAIN;
	}
	return (wavetable);
}

t_wavetable	tri_wave(t_note note)
{
	if (note.pitch == 0.f)
		return((t_wavetable){.samples = NULL, .size = 0});
	float	x = 0.0f;
	float	sine_value = 0.0f;
	t_wavetable wavetable;

	wavetable.size = SAMPLE_RATE / note.pitch;
	wavetable.samples = malloc(sizeof(wavetable.samples) * wavetable.size);
	if (wavetable.samples == NULL)
	{
		exit(1);
	}
	for (size_t i = 0; i < wavetable.size; i++)
	{
		sine_value = sin(((float) i / (float) SAMPLE_RATE) * 2.0f * M_PI * note.pitch);
		x += ((sine_value < 0.0f) ? -0.01 : 0.01);
		wavetable.samples[i] = x * GAIN;
	}
	return (wavetable);
}

t_wavetable	square_wave(t_note note)
{
	if (note.pitch == 0.f)
		return((t_wavetable){.samples = NULL, .size = 0});
	float	x = 0.0f;
	float	sine_value = 0.0f;
	t_wavetable wavetable;

	wavetable.size = SAMPLE_RATE / note.pitch;
	wavetable.samples = malloc(sizeof(wavetable.samples) * wavetable.size);
	if (wavetable.samples == NULL)
	{
		exit(1);
	}
	for (size_t i = 0; i < wavetable.size; i++)
	{
		x += 1.0f;
		sine_value = sin((x / (float) SAMPLE_RATE) * 2.0f * M_PI * note.pitch);
		wavetable.samples[i] = (sine_value < 0) ? GAIN : -GAIN;
	}
	return (wavetable);
}
