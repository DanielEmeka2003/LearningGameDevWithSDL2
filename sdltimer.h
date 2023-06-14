#ifndef SDLTIMER_H
#define SDL_TIMER_H

#pragma once

#include "C:\Users\MIKE EMEKA\Documents\C++\includes.h"
#include "SDLincludes.h"

class Sdltimer
{
	std::uint64_t m_startTime{}, m_pausedTime{};
	bool m_timerIsStarted{}, m_timerIsPaused{}, m_timerIsZero{ true };
	
public:
	Sdltimer() = default;
	Sdltimer(const Sdltimer&) = default;
	Sdltimer(Sdltimer&&) = default;

	Sdltimer& operator=(const Sdltimer&) = default;
	Sdltimer& operator=(Sdltimer&&) = default;

	void startTimer();
	void restartTimer();
	void zeroTimer();
	void pauseTimer();
	void unpauseTimer();

	template <typename T>
	T getSeconds();
	
	std::uint64_t getMilliseconds();
};


template <typename T>
T Sdltimer::getSeconds()
{
	if (m_timerIsStarted and !m_timerIsPaused)
		return static_cast<T>((m_pausedTime + (SDL_GetTicks64() - m_startTime)) / T{ 1000 });

	if (m_timerIsZero)
		return T{};

	if (m_timerIsStarted and m_timerIsPaused)
		return static_cast<T>(m_pausedTime / T{ 1000 });

	return  T{};
}

template <>
inline char Sdltimer::getSeconds<char>()
{
	assert(false and "template of type char is not allowed.");
	return char{};
}

template <>
inline bool Sdltimer::getSeconds<bool>()
{
	assert(false and "template of type bool is not allowed.");
	return bool{};
}

#endif // !SDLTIMER_H
