#pragma once

extern "C"{
	#include <libavformat/avformat.h>	// Muxers & codecs
}

namespace AV{
	// Media files demuxer
	class Demuxer{
		public:
			Demuxer(const char* filename);

			// TODO

	};
}
