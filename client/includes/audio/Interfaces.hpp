#pragma once

#include "portaudio.h"

#include <string>

namespace babel::audio
{

	//Opus objects

	class IDecoder
	{
	public:
		virtual soundbuffer decode_audio(const compressed_soundbuffer &) const = 0;
	};

	class IEncoder
	{
	public:
		virtual compressed_soundbuffer encode_audio(const soundbuffer &) const = 0;
	};

	//portaudio objects

	class IDevice
	{
	public:
		virtual void start_stream() = 0;
		virtual void stop_stream() = 0;
	};

	class IInput : public IDevice
	{
	public:
		virtual soundbuffer get_sound() = 0;
	};

	class IOutput : public IDevice
	{
	public:
		virtual void set_sound(const soundbuffer &, const std::string &) = 0;
	};
}