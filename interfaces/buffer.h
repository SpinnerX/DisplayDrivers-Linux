#pragma once
#include <array>
#include <cstdint>
#include <iostream>

struct pixel_t{
	uint8_t r, g, b, a;
};


template<size_t Width, size_t Height>
struct Framebuffer{

	uint8_t* data() { return bufferData.data(); }

	size_t width() const { return Width; }

	size_t height() const { return Height; }

	std::array<pixel_t, Width * Height> bufferData;
};


template<typename BufferType>
class DisplayDriverTemplated{
public:
	DisplayDriverTemplated(BufferType& buffer) : buffers(&buffer){}
	
	void draw_pixel(int x, int y, pixel_t pixel){
		// buffers->draw(x, y, pixel);
		/* std::cout << "Called!\n"; */
		setCursorPosition(y, x);
		std::cout << "\033[48;2;" << (int)pixel.r << ";" << (int)pixel.g << ";" << (int)pixel.b << "m \n"; // Set background color to RGB and output a space
		std::cout << "\033[0m"; // Reset text formatting
	}

	void draw_line(){}
	
	/* void display(){} */

private:

	void setCursorPosition(int x, int y){
		clearscreen();
		std::cout << "\033[" << y << ";" << x << "H";
	}

	//Clears the screen
	//Example: clearscreen();
	inline void clearscreen() {
		std::cerr << "\033[2J";
	}
	


private:
	BufferType* buffers;
};

class DisplayDriver{
public:
	
	DisplayDriver(void* framebuffer);

	template<int x, int y, int Width, int Height>
	void draw_pixel(){
		draw_pixel(x, y, Width, Height);
	}

	void display(){}

private:
	void draw_pixel(int x, int y, int Width, int Height){
		/* std::cerr << "\033[48;2;" << pixel.r << ";" << pixel.g << ";" << pixel.b << "m"; */
	}

private:
	/* Buffer* framebuffer; */
	void* framebuffer = nullptr;
};
