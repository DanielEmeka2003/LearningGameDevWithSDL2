#ifndef AUDIO_H
#define AUDIO_H

#pragma once

#include "SDLincludes.h"
#include "C:\Users\MIKE EMEKA\Documents\C++\includes.h"
#include "error_file.h"

class Audio
{
public:

	enum AudioType
	{
		music,
		soundeffect,
	};

private:

	static constexpr int default_channel{ -1 };
	static constexpr int default_nloopinf{ -1 };

	Mix_Music* m_music{};
	Mix_Chunk* m_chunk{};
	AudioType m_AT{};

	Error_file err{ "C:/Users/MIKE EMEKA/Documents/AudioErrorFile/", true, "errorFile.txt" };
	
public:

	Audio(AudioType typeOfAudio);

	Audio() = default;
	Audio(const Audio&) = default;
	Audio(Audio&&) = default;

	Audio& operator=(const Audio&) = default;
	Audio& operator=(Audio&&) = default;
	
	~Audio();

	void free();

	void loadAudio(std::string path);
	void playSoundEffect(int channel = default_channel, int nloop = 0);
	void playMusic(int nloop = default_nloopinf);
	void pauseMusic();
	void stopMusic();
	void resumeMusic();
	void rewindMusic();
};



#endif // !AUDIO_H
