#pragma once

#include <vector>
#include <string>

// Player to output uncompressed audio to default device
class AudioPlayer{
	public:
		// Available sample formats
		enum SampleType{U8, S8, S16, S24, S32, F32};
	private:
		// Output format data
		const unsigned sample_rate;
		const unsigned short channels;
		const SampleType sample_type;
		const int device_index;
		// Last error
		int err;
		// Portaudio initialized
		bool initialized;
		// Audio stream object
		void* stream;
	public:
		// Create audio stream
		AudioPlayer(unsigned sample_rate = 44100, unsigned short channels = 1, SampleType sample_type = F32, int device_index = -1);
		// Delete audio stream
		~AudioPlayer();
		// Get output format data (from ctor)
		unsigned GetSampleRate() const;
		unsigned short GetChannels() const;
		SampleType GetSampleType() const;
		int GetDeviceIndex() const;
		// Get current error message or zero
		const char* GetError();
		// Send data to audio output
		void Send(const void* data, unsigned long frames);
		// Get audio output devices
		struct Device{
			std::string name;
			std::string host_api;
			int index;
			int channels;
			bool is_default;
		};
		static std::vector<Device> GetDevices();
	private:
		// No copy
		AudioPlayer(const AudioPlayer&);
		AudioPlayer& operator =(const AudioPlayer&);
};
