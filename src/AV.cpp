#include "AV.hpp"
extern "C"{
	#include <libswscale/swscale.h>	// Video frames converter
	#include <libswresample/swresample.h>	// Audio samples converter
}

namespace AV{
	Demuxer::Demuxer(const char* filename){
		av_register_all();

		// TODO

	}
}