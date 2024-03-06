#include "interfaces/buffer.h"
using namespace std;



int main(){
	Framebuffer<128, 64> framebuffers;

	DisplayDriverTemplated driver(framebuffers);
	driver.drawSquare(0, 5, {.r=255, .g=255, .b=255});
	
	driver.display();

	return 0;
}
