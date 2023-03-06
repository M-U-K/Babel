#include "Handler.hpp"

babel::audio::Handler::Handler(): m_input(std::make_unique<Pa_Input>()), m_output(std::make_unique<Pa_Output>()), m_encoder(std::make_unique<Op_Encoder>())
{
}

babel::audio::Handler::~Handler()
{
	m_decoders.clear();
}

void babel::audio::Handler::start_record() const
{
	m_input->start_stream();
}

void babel::audio::Handler::stop_record() const
{
	m_input->stop_stream();
}

void babel::audio::Handler::start_playback() const
{
	m_output->start_stream();
}

void babel::audio::Handler::stop_playback() const
{
	m_output->stop_stream();
}

void babel::audio::Handler::queue(const compressed_soundbuffer& rbuffer, const std::string& id)
{
	m_decoders.try_emplace(id, std::make_unique<Op_Decoder>());
	m_output->set_sound(m_decoders[id]->decode_audio(rbuffer), id);
}