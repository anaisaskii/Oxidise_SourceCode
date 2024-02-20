#pragma once
#include <SDL_mixer.h>
#include <sstream>
#include <vector>

using namespace std;

class Audio 
{
public:
	Audio();

	virtual ~Audio();

	void PlaySound(); //for playing bg music

	void PlaySoundEffect(); //for playing sound effects

private:
	Mix_Music* musicPlayer; //Mix_Music for longer audio (bg music)

	Mix_Chunk* soundEffectPlayer; //Mix_Chunk for short sound effects
};
