#include "AudioPlayer.hpp"
#include <portaudio.h>

AudioPlayer::AudioPlayer(unsigned sample_rate, unsigned short channels, SampleType sample_type, int device_index)
: sample_rate(sample_rate), channels(channels), sample_type(sample_type), device_index(device_index), stream(0){
	// Initialize Portaudio
	this->err = Pa_Initialize();
	this->initialized = this->err == paNoError;
	// Create audio stream
	if(this->err == paNoError){
		PaSampleFormat sample_format;
		switch(sample_type){
			case U8: sample_format = paUInt8; break;
			case S8: sample_format = paInt8; break;
			case S16: sample_format = paInt16; break;
			case S24: sample_format = paInt24; break;
			case S32: sample_format = paInt32; break;
			case F32: sample_format = paFloat32; break;
			default:
				this->err = paSampleFormatNotSupported;
				return;
		}
		if(device_index == -1)
			device_index = Pa_GetDefaultOutputDevice();
		if(Pa_GetDeviceInfo(device_index) == 0){
			this->err = paInvalidDevice;
			return;
		}
		const PaStreamParameters outputParameters = {
			device_index,
			channels,
			sample_format,
			Pa_GetDeviceInfo(device_index)->defaultHighOutputLatency,
			0
		};
		this->err = Pa_OpenStream(&this->stream, 0, &outputParameters, sample_rate, paFramesPerBufferUnspecified, paNoFlag, 0, 0);
		if(this->err == paNoError)
			this->err = Pa_StartStream(this->stream);
	}
}

AudioPlayer::~AudioPlayer(){
	// Close audio stream
	if(this->stream)
		Pa_CloseStream(this->stream);
	// Deinitialize Portaudio
	if(this->initialized)
		Pa_Terminate();
}

unsigned AudioPlayer::GetSampleRate() const{
	return this->sample_rate;
}

unsigned short AudioPlayer::GetChannels() const{
	return this->channels;
}

AudioPlayer::SampleType AudioPlayer::GetSampleType() const{
	return this->sample_type;
}

int AudioPlayer::GetDeviceIndex() const{
	return this->device_index;
}

const char* AudioPlayer::GetError(){
	return this->err != paNoError ? Pa_GetErrorText(this->err) : 0;
}

void AudioPlayer::Send(const void* data, unsigned long frames){
	if(this->stream)
		this->err = Pa_WriteStream(this->stream, data, frames);
}

std::vector<AudioPlayer::Device> AudioPlayer::GetDevices(){
	std::vector<AudioPlayer::Device> devices;
	if(Pa_Initialize() != paNoError)
		return devices;
	int device_count = Pa_GetDeviceCount();
	for(int i = 0; i < device_count; ++i){
		const PaDeviceInfo* device_info = Pa_GetDeviceInfo(i);
		if(device_info->maxOutputChannels > 0)
			devices.push_back({device_info->name, Pa_GetHostApiInfo(device_info->hostApi)->name, i, device_info->maxOutputChannels, i == Pa_GetDefaultOutputDevice()});
	}
	Pa_Terminate();
	return devices;
}
