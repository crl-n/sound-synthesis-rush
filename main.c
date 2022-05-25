/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:51:46 by cnysten           #+#    #+#             */
/*   Updated: 2022/05/25 12:39:29 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <stdio.h>
#include <strings.h>

#include "minisynth.h"

void	play(t_song song)
{
	(void) song;
	return ;
}

t_song	parse(char *filename)
{
	(void) filename;
	t_song	song;
	bzero(&song, sizeof (t_song));
	return (song);
}

void	init_sdl(void)
{
	return ;
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	if (argc == 2)
	{
		t_song	song = parse(argv[1]);
		init_sdl();
		play(song);
		printf("🎵\n");
	}
	printf("Usage: ./minisynth [file]\n");

	return (0);
}
