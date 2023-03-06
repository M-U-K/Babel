#pragma once

#include <array>
#include <vector>
#include <cstring>
#include <cstdint>

namespace babel::audio
{
	constinit double const default_sample_rate = 48000.0;
	constinit size_t const default_frames_per_buffers = 512;
	constinit int const default_channel_count = 2;
	constinit int const default_elements_buffer = default_frames_per_buffers * default_channel_count;

	struct soundbuffer
	{
		soundbuffer(): m_samples({})
		{
			m_samples.fill(0);
		};
		soundbuffer(const float* ptr)
		{
			std::memcpy(m_samples.data(), ptr, default_elements_buffer * sizeof(float));
		};

		std::array<float, default_elements_buffer> m_samples;
	};

	struct compressed_soundbuffer
	{
		compressed_soundbuffer()
		{
			m_samples.resize(default_elements_buffer);
			std::fill(m_samples.begin(), m_samples.end(), 0);
		};

		std::vector<uint8_t> m_samples;
		int32_t m_size;
	};
}
