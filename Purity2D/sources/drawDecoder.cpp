
#include "../libs/drawDecoder.hpp"

DrawDecoder* DrawDecoder::instance = nullptr;

DrawDecoder* DrawDecoder::get() {
	if (instance == nullptr) {
		instance = new DrawDecoder();
	}
	return instance;
}