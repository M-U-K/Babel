#include "Types.hpp"
#include "Codecs.hpp"

#include <stdexcept>
//Encoder

babel::audio::Op_Encoder::Op_Encoder(): m_encoder(nullptr)
{
	int err(OPUS_OK);

	m_encoder = opus_encoder_create(default_sample_rate, default_channel_count, OPUS_APPLICATION_VOIP, &err);
	if (err != OPUS_OK)
		throw std::invalid_argument("encoder error");
}

babel::audio::Op_Encoder::~Op_Encoder()
{
	if (m_encoder)
		opus_encoder_destroy(m_encoder);
}

babel::audio::compressed_soundbuffer babel::audio::Op_Encoder::encode_audio(const soundbuffer& buffer) const
{
	compressed_soundbuffer tmp;
	opus_int32 encode = opus_encode_float(m_encoder, buffer.m_samples.data(), default_frames_per_buffers, tmp.m_samples.data(), default_elements_buffer);
	
	tmp.m_size = encode;
	if (encode < OPUS_OK)
		throw std::invalid_argument("encoder error");
	return tmp;
}

//Decoder

babel::audio::Op_Decoder::Op_Decoder(): m_decoder(nullptr)
{
	int err(OPUS_OK);

	m_decoder = opus_decoder_create(default_sample_rate, default_channel_count, &err);
	if (err != OPUS_OK)
		throw std::invalid_argument("decoder error");
}

babel::audio::Op_Decoder::~Op_Decoder()
{
	if (m_decoder)
		opus_decoder_destroy(m_decoder);
}

babel::audio::soundbuffer babel::audio::Op_Decoder::decode_audio(const compressed_soundbuffer& buffer) const
{
	soundbuffer tmp;
	int decode = opus_decode_float(m_decoder, buffer.m_samples.data(), buffer.m_size, tmp.m_samples.data(), default_frames_per_buffers, 0);

	if (decode < OPUS_OK)
		throw std::invalid_argument("decoder error");
	return tmp;
}