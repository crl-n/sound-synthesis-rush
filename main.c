/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cnysten <cnysten@student.hive.fi>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/05/25 11:51:46 by cnysten		   #+#	#+#			 */
/*   Updated: 2022/05/25 15:53:07 by carlnysten       ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_audio.h>
#include <SDL_mixer.h>
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
	long long int	i;
	int8_t			sample;
	int				sample_size = sizeof(int8_t);

	i = 0;
	while (i++ < 80000)
	{
		sample = wave_functions[note.pitch](audio_device, note.duration);
		SDL_QueueAudio(audio_device, &sample, sample_size);
	}
	SDL_PauseAudioDevice(audio_device, 0);
	SDL_Delay(3000);
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
	audio_spec.format = AUDIO_S8;
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

		if (strcmp(argv[1], "-d") == 0)
		{
			t_note	note;

			note.pitch = a;
			note.duration = 1000;
			play_wave(audio_device, note);
			printf("Debug 🎵\n");
		}
		else
		{
			t_song	song = parse(argv[1]);
			play(song, audio_device);
			printf("🎵\n");
		}
	}
	else
	{
		printf("Usage: ./minisynth [file]\n");
	}
	return (0);
}
