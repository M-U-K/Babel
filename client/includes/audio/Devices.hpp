#pragma once

#include "Interfaces.hpp"

#include <portaudio.h>
#include <deque>
#include <unordered_map>

namespace babel::audio
{
	class Pa_Input : public IInput
	{
	public:
		explicit Pa_Input();
		~Pa_Input();

		void start_stream() override;
		void stop_stream() override;
		soundbuffer get_sound() override;
		
	private:
		static int callback(const void*, void*, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void*);
		PaStream* m_stream;
		PaStreamParameters m_params{};
		std::deque<soundbuffer> m_buffers;
	};

	class Pa_Output : public IOutput
	{
	public:
		Pa_Output();
		~Pa_Output();

		void start_stream() override;
		void stop_stream() override;
		void set_sound(const soundbuffer &, const std::string &) override;

	private:
		static int callback(const void*, void*, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void*);
		PaStream* m_stream;
		PaStreamParameters m_params{};
		std::unordered_map<std::string, std::deque<soundbuffer>> m_buffers;
	};

}