#pragma once

#include "Types.hpp"
#include "Interfaces.hpp"

#include <opus.h>

namespace babel::audio
{
	class Op_Encoder : public IEncoder
	{
	public:
		Op_Encoder();
		~Op_Encoder();

		compressed_soundbuffer encode_audio(const soundbuffer&) const override;
	private:
		OpusEncoder* m_encoder;
	};

	class Op_Decoder : public IDecoder
	{
	public:
		Op_Decoder();
		~Op_Decoder();

		soundbuffer decode_audio(const compressed_soundbuffer&) const override;
	private:
		OpusDecoder* m_decoder;
	};
}