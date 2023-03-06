#pragma once

#include "Types.hpp"
#include "Devices.hpp"
#include "Codecs.hpp"

#include <unordered_map>
#include <memory>

namespace babel::audio
{
	class Handler
	{
	public:
		Handler();
		~Handler();

		void start_record() const;
		void stop_record() const;
		void start_playback() const;
		void stop_playback() const;
		void queue(const audio::compressed_soundbuffer&, const std::string&);

	private:
		std::unique_ptr<Pa_Input> m_input;
		std::unique_ptr<Pa_Output> m_output;
		std::unique_ptr<Op_Encoder> m_encoder;
		std::unordered_map<std::string, std::unique_ptr<Op_Decoder>> m_decoders;
	};
}