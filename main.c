/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cnysten <cnysten@student.hive.fi>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/05/25 11:51:46 by cnysten		   #+#	#+#			 */
/*   Updated: 2022/05/25 19:19:51 by cnysten          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_audio.h>
#include <stdio.h>
#include <strings.h>

#include "minisynth.h"

void	play(t_song song, SDL_AudioDeviceID audio_device)
{
	long long int	i;
	int8_t			sample;
	int				sample_size = sizeof(int8_t);

	i = 0;
	(void) song;
	sample = 0;
	while (i++ < 80000)
	{
		sample++; 
		SDL_QueueAudio(audio_device, &sample, sample_size);
	}
	SDL_PauseAudioDevice(audio_device, 0);
	SDL_Delay(3000);
	return ;
}

void	play_wave(SDL_AudioDeviceID audio_device, t_note note)
{
	wave_functions[3](audio_device, note);
	SDL_PauseAudioDevice(audio_device, 0);
	SDL_Delay(SDL_GetQueuedAudioSize(audio_device) / 2 / FREQ * 1000);
	return ;
}

t_song	parse(char *filename)
{
	(void) filename;
	t_song	song;
	bzero(&song, sizeof (t_song));
	return (song);
}

SDL_AudioDeviceID	init_sdl(void)
{
	SDL_Init(SDL_INIT_AUDIO);
	SDL_AudioDeviceID audio_device;
	SDL_AudioSpec audio_spec;
	SDL_zero(audio_spec);
	audio_spec.freq = 44100;
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

			note.pitch = a;
			if (argv[1][2])
				note.pitch = argv[1][2] - 'a' + 1;
			note.duration = 5;
			printf("Debug 🎵\n");
			play_wave(audio_device, note);
		}
		else
		{
			t_song	song = parse(argv[1]);
			printf("🎵\n");
			play(song, audio_device);
		}
	}
	else
	{
		printf("Usage: ./minisynth [file]\n");
	}
	return (0);
}
