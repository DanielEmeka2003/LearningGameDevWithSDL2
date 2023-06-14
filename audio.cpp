#include "audio.h"

Audio::Audio(AudioType typeOfAudio): m_AT{ typeOfAudio }
{}

Audio::~Audio()
{
	free();
}

void Audio::free()
{
	if (m_music)
	{
		Mix_FreeMusic(m_music);
		m_music = nullptr;
	}
	if (m_chunk)
	{
		Mix_FreeChunk(m_chunk);
		m_chunk = nullptr;
	}
}

void Audio::loadAudio(std::string path)
{
	free();

	err.openFile();

	switch (m_AT)
	{
	case Audio::music:

		if (!(m_music = Mix_LoadMUS(path.c_str()) ))
		{
			err.InsertErrorMessageToFile() << "Unable to load music.\n";
			err.InsertErrorMessageToFile() << "Sdl_mixer Error: " << Mix_GetError() << '\n';
			err.getErrorNotification();

			std::exit(1);
		}

		break;
	case Audio::soundeffect:
		
		if (!(m_chunk = Mix_LoadWAV(path.c_str()) ))
		{
			err.InsertErrorMessageToFile() << "Unable to load soundeffect.\n";
			err.InsertErrorMessageToFile() << "Sdl_mixer Error: " << Mix_GetError() << '\n';
			err.getErrorNotification();

			std::exit(1);
		}

		break;
	default:
		assert(false and "Not an Audio Type\n");
		break;
	}
}
void Audio::playSoundEffect(int channel, int nloop)
{
	if (m_AT == music)
		return;

	err.openFile();

	if (Mix_PlayChannel(channel, m_chunk, nloop) == -1)
	{
		err.InsertErrorMessageToFile() << "In public member function playSoundEffect: unable to play soundeffect.\n";
		err.InsertErrorMessageToFile() << "Sdl_mixer Error: " << Mix_GetError() << '\n';
	}
}
void Audio::playMusic(int nloop)
{
	if (m_AT == soundeffect)
		return;

	err.openFile();

	if (!Mix_PlayingMusic())
	{
		if (Mix_PlayMusic(m_music, nloop))
		{
			err.InsertErrorMessageToFile() << "In public member function playMusic: unable to play music.\n";
			err.InsertErrorMessageToFile() << "Sdl_mixer Error: " << Mix_GetError() << '\n';
		}
	}
}
void Audio::pauseMusic()
{
	if (m_AT == soundeffect)
		return;
	if (!Mix_PausedMusic())
	{
		Mix_PauseMusic();
	}
}
void Audio::stopMusic()
{
	if (m_AT == soundeffect)
		return;
	Mix_HaltMusic();
}
void Audio::resumeMusic()
{
	if (m_AT == soundeffect)
		return;
	if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
}
void Audio::rewindMusic()
{
	if (m_AT == soundeffect)
		return;
	Mix_RewindMusic();
}
