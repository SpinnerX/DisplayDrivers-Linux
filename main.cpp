#include <iostream>
#include "interfaces/Framebuffer.h"
using namespace std;


int main(){
	constexpr uint32_t width = 5;
	constexpr uint32_t height = 10;
	libhal::Framebuffer<width, height> framebuffers;
	libhal::pixel_t pixel1 = {255, 255, 255};
	
	if(!framebuffers.read(pixel1)){}

	return 0;
}
