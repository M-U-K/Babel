#include "Types.hpp"
#include "Devices.hpp"

#include <stdexcept>

//PortAudio Input device

babel::audio::Pa_Input::Pa_Input(): m_stream(nullptr)
{
	PaError err = Pa_Initialize();

	if (err != paNoError)
		throw std::invalid_argument(Pa_GetErrorText(err));

	m_params = { Pa_GetDefaultInputDevice(), default_channel_count, paFloat32};

	if (m_params.device == paNoDevice)
		throw std::invalid_argument("no device input");
	m_params.suggestedLatency = Pa_GetDeviceInfo(m_params.device)->defaultLowInputLatency;
	m_params.hostApiSpecificStreamInfo = nullptr;
}

babel::audio::Pa_Input::~Pa_Input()
{
	if (!Pa_IsStreamStopped(m_stream))
		Pa_AbortStream(m_stream);
	Pa_Terminate();
}

void babel::audio::Pa_Input::start_stream()
{
	if (Pa_OpenStream(&m_stream, &m_params, nullptr, default_sample_rate, default_frames_per_buffers, paClipOff, &callback, this) != paNoError)
		throw std::invalid_argument("stream input error");
	if (Pa_StartStream(m_stream) != paNoError)
		throw std::invalid_argument("stream input error");
}

void babel::audio::Pa_Input::stop_stream()
{
	m_buffers.clear();
	if (Pa_CloseStream(m_stream) != paNoError)
		throw std::invalid_argument("stream input error");
}

babel::audio::soundbuffer babel::audio::Pa_Input::get_sound()
{
	soundbuffer first = m_buffers.front();

	m_buffers.pop_front();
	return first;
}

int babel::audio::Pa_Input::callback(const void* input, void* output, unsigned long frames, const PaStreamCallbackTimeInfo* info, PaStreamCallbackFlags flags, void* data)
{
	Pa_Input* device = reinterpret_cast<Pa_Input*>(data);
	const float* inc_buffer = reinterpret_cast<const float*>(input);

	device->m_buffers.emplace_back(inc_buffer);
	return paContinue;
}

//PortAudio Output device

babel::audio::Pa_Output::Pa_Output(): m_stream(nullptr)
{
	PaError err = Pa_Initialize();

	if (err != paNoError)
		throw std::invalid_argument(Pa_GetErrorText(err));

	m_params = { Pa_GetDefaultOutputDevice(), default_channel_count, paFloat32 };

	if (m_params.device == paNoDevice)
		throw std::invalid_argument("no device output");
	m_params.suggestedLatency = Pa_GetDeviceInfo(m_params.device)->defaultLowInputLatency;
	m_params.hostApiSpecificStreamInfo = nullptr;
}

babel::audio::Pa_Output::~Pa_Output()
{
	if (!Pa_IsStreamStopped(m_stream))
		Pa_AbortStream(m_stream);
	Pa_Terminate();
}

void babel::audio::Pa_Output::start_stream()
{
	if (Pa_OpenStream(&m_stream, nullptr, &m_params, default_sample_rate, default_frames_per_buffers, paClipOff, &callback, this) != paNoError)
		throw std::invalid_argument("stream output error");
	if (Pa_StartStream(m_stream) != paNoError)
		throw std::invalid_argument("stream output error");
}

void babel::audio::Pa_Output::stop_stream()
{
	m_buffers.clear();
	if (Pa_CloseStream(m_stream) != paNoError)
		throw std::invalid_argument("stream output error");
}

void babel::audio::Pa_Output::set_sound(const babel::audio::soundbuffer& rbuffer, const std::string& id)
{
	m_buffers[id].push_back(rbuffer);
}

int babel::audio::Pa_Output::callback(const void* input, void* output, unsigned long frames, const PaStreamCallbackTimeInfo* info, PaStreamCallbackFlags flags, void* data)
{
	Pa_Output* device = reinterpret_cast<Pa_Output*>(data);
	float* inc_buffer = reinterpret_cast<float*>(output);

	std::memset(inc_buffer, 0, default_elements_buffer * sizeof(float));
	
	for (auto it = device->m_buffers.begin(); it != device->m_buffers.end();) {
		auto& pair = *it;

		++it;
		if (pair.second.empty()) {
			device->m_buffers.erase(pair.first);
			continue;
		}
		auto& soundBuffer = pair.second.front();
		for (int i = 0; i < default_elements_buffer; ++i) {
			inc_buffer[i] += soundBuffer.m_samples[i];
		}
		pair.second.pop_front();
	}
	return paContinue;
}