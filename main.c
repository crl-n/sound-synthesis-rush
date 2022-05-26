/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cnysten <cnysten@student.hive.fi>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/05/25 11:51:46 by cnysten		   #+#	#+#			 */
/*   Updated: 2022/05/26 14:44:41 by cnysten          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_audio.h>
#include <stdio.h>
#include <strings.h>

#include "minisynth.h"

void	play(t_song *song, SDL_AudioDeviceID audio_device)
{
	for (size_t i = 0; i < song->size; i++)
	{
		SDL_QueueAudio(audio_device, &song->master[i], SAMPLE_SIZE);
	}
	SDL_PauseAudioDevice(audio_device, 0);
	SDL_Delay(SAMPLE_RATE / song->size * 1000);
	return ;
}

void	play_wave(SDL_AudioDeviceID audio_device, t_note note)
{
	int	delay;

	wave_functions[0](note);
//	wave_functions[1](audio_device, note);
//	wave_functions[2](audio_device, note);
//	wave_functions[3](audio_device, note);
	SDL_PauseAudioDevice(audio_device, 0);
	delay = SDL_GetQueuedAudioSize(audio_device) / 2 / SAMPLE_RATE * 1000;
	printf("Delay: %d", delay);
	SDL_Delay(delay);
	return ;
}

SDL_AudioDeviceID	init_sdl(void)
{
	SDL_Init(SDL_INIT_AUDIO);

	SDL_AudioDeviceID audio_device;
	SDL_AudioSpec audio_spec;

	SDL_zero(audio_spec);
	audio_spec.freq = SAMPLE_RATE;
	audio_spec.format = AUDIO_S16SYS;
	audio_spec.channels = 2;
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
			//if (argv[1][2] <= 'g' && argv[1][2] >= 'a')
			//	note.pitch = argv[1][2] - 'a' + 1;
			note.duration = 2 * SAMPLE_RATE;
			printf("Debug 🎵\n");
			play_wave(audio_device, note);
		}
		else
		{
			t_song	song = parse(argv[1]);
			printf("🎵\n");
			play(&song, audio_device);
		}
	}
	else
	{
		printf("Usage: ./minisynth [file]\n");
	}
	return (0);
}
