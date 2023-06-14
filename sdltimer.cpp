#include "sdltimer.h"

void Sdltimer::startTimer()
{
	if (!m_timerIsStarted)
	{
		m_startTime = SDL_GetTicks64();
		m_pausedTime = 0;
		m_timerIsPaused = false;
		m_timerIsStarted = true;
		m_timerIsZero = false;
	}
}

void Sdltimer::restartTimer()
{
	if (!m_timerIsZero)
	{
		m_startTime = SDL_GetTicks64();
		m_pausedTime = 0;
		m_timerIsPaused = false;
		m_timerIsStarted = true;
		m_timerIsZero = false;
	}
}

void Sdltimer::zeroTimer()
{
	if (m_timerIsStarted)
	{
		m_startTime = 0;
		m_pausedTime = 0;
		m_timerIsPaused = false;
		m_timerIsStarted = false;
		m_timerIsZero = true;
	}
}

void Sdltimer::pauseTimer()
{
	if (!m_timerIsZero)
	{
		m_pausedTime = m_pausedTime + (SDL_GetTicks64() - m_startTime);
		m_startTime = 0;
		m_timerIsPaused = true;
		m_timerIsStarted = true;
		m_timerIsZero = false;
	}
}

void Sdltimer::unpauseTimer()
{
	if (!m_timerIsZero)
	{
		m_startTime = SDL_GetTicks64();
		m_timerIsPaused = false;
		m_timerIsStarted = true;
		m_timerIsZero = false;
	}
}

std::uint64_t Sdltimer::getMilliseconds()
{
	if (m_timerIsStarted and !m_timerIsPaused)
		return (m_pausedTime + (SDL_GetTicks64() - m_startTime));

	if (m_timerIsZero)
		return 0;
	
	if (m_timerIsStarted and m_timerIsPaused)
		return m_pausedTime;

	return 0;
}
