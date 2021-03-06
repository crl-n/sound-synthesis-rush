/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 20:31:40 by cnysten           #+#    #+#             */
/*   Updated: 2022/05/27 23:54:24 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_audio.h>
#include <stdio.h>
#include <strings.h>
#include "minisynth.h"

void	play(t_song *song, SDL_AudioDeviceID audio_device)
{
	int16_t		sample_input;
	uint32_t	delay;

	for (size_t i = 0; i < song->size; i++)
	{
		sample_input = (int16_t)(song->master[i].sample * GAIN);
		SDL_QueueAudio(audio_device, &sample_input, SAMPLE_SIZE);
	}
	SDL_PauseAudioDevice(audio_device, 0);
	delay = song->length / SAMPLE_RATE * 1000 + 500;
	SDL_Delay(delay);
	return ;
}

void	play_wave(SDL_AudioDeviceID audio_device, t_note note)
{
	int	delay;

	wave_functions[0](note);
	SDL_PauseAudioDevice(audio_device, 0);
	delay = SDL_GetQueuedAudioSize(audio_device) / 2 / SAMPLE_RATE * 1000;
	SDL_Delay(delay);
	return ;
}

SDL_AudioDeviceID	init_sdl(void)
{
	SDL_AudioDeviceID audio_device;
	SDL_AudioSpec audio_spec;

	SDL_Init(SDL_INIT_AUDIO);
	SDL_zero(audio_spec);
	audio_spec.freq = SAMPLE_RATE;
	audio_spec.format = AUDIO_S16SYS;
	audio_spec.channels = 1;
	audio_spec.samples = 1024;
	audio_spec.callback = NULL;
	audio_device = SDL_OpenAudioDevice(
		NULL, 0, &audio_spec, NULL, 0);
	return (audio_device);
}

int	main(int argc, char **argv)
{
	SDL_AudioDeviceID audio_device;

	if (argc == 2)
	{
		audio_device = init_sdl();
		if (strncmp(argv[1], "-d", 2) == 0)
		{
			t_note	note;

			note.pitch = 440.0f;
			note.duration = 2 * SAMPLE_RATE;
			printf("Debug ????\n");
			play_wave(audio_device, note);
		}
		else
		{
			t_song	song = parse(argv[1]);
			mix_song_volume(&song);
			printf("????\n");
			play(&song, audio_device);
			free(song.master);
		}
		SDL_CloseAudioDevice(audio_device);
		SDL_Quit();
	}
	else
	{
		printf("Usage: ./minisynth [file]\n");
	}
	return (0);
}
