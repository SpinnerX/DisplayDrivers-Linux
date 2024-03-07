#include "interfaces/buffer.h"
#include <unistd.h>
using namespace std;

template<size_t SIZE>
struct IndexBuffer{

	void* data() const { return indices; }
	
	size_t size() const  { return indices.size(); }

	std::array<uint8_t, SIZE> indices;
};

template<size_t Width, size_t Height>
struct TestFrameBuffers{
	

};

int main(){
	Framebuffer<128, 64> framebuffers;

	DisplayDriver driver(framebuffers);
	/* driver.draw_pixel(0, 5, {.r=255, .g=255, .b=255}); */
	/* driver.draw_line(5, 5, 15, 10, {.r=255, .g=255, .b=255}); */

	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 20; j++){
			driver.refresh();
			driver.draw_square({i, j}, 10, 10, {.r=0, .g=0, .b=255});
			sleep(1);
		}
	}
	/* driver.draw_square({.x = 8, .y=6}, 10, 10, {.r=255, .g=0, .b=0}); */

	return 0;
}
