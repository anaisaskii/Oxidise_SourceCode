#include "Audio.h"

Audio::Audio()
{
	//checking for error with opening file
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1) {
		printf("Audio mixer could not be created, SDL_Error %s\n", SDL_GetError());
	}

	//file paths for music and sound effects
	musicPlayer = Mix_LoadMUS("assets/bgmusic.mp3");
	soundEffectPlayer = Mix_LoadWAV("assets/laser.wav");

	if (!musicPlayer || !soundEffectPlayer) {
		printf("Failed to load MP3/WAV file: %s\n", Mix_GetError());
	}

	//setting volume for sound effect
	Mix_Volume(-1, 20); //chennel, volume
	Mix_VolumeMusic(20);
}

Audio::~Audio()
{
	//Free up resources upon creation
	if (musicPlayer) 
	{
		Mix_FreeMusic(musicPlayer);
	}

	if (soundEffectPlayer)
	{
		Mix_FreeChunk(soundEffectPlayer);
	}
}

//Play background music
void Audio::PlaySound()
{
	Mix_PlayMusic(musicPlayer, -1);
}

//Play sound effects
void Audio::PlaySoundEffect() 
{
	Mix_PlayChannel(-1, soundEffectPlayer, 0);
}