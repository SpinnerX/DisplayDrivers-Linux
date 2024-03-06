#pragma once
#include <array>
#include <cstdint>
#include <iostream>

struct pixel_t{
	uint8_t r, g, b, a;
};

struct vec2{
	int x=0, y=0;
};

template<size_t Width, size_t Height>
struct Colorbuffer{
	
	pixel_t get(int x, int y){
		return buffer[y * Width + x];
	}

	std::array<pixel_t, Width * Height> buffer;
};

struct Depthbuffer{
};

template<size_t Width, size_t Height>
struct Framebuffer{

	uint8_t* data() { return buffer.data(); }

	size_t width() const { return Width; }

	size_t height() const { return Height; }

	std::array<pixel_t, Width * Height> buffer;
};

template<typename BufferType>
class DisplayDriver{
public:
	DisplayDriver(BufferType& buffer) : buffers(&buffer){}
	
	// @note function for drawing single pixels from the terminal
	void draw_pixel(int x, int y, pixel_t pixel){
		// @note this is an example usage: buffers->draw(x, y, pixel);
		setCursorPosition(x, y);
		std::cout << "\033[48;2;" << (int)pixel.r << ";" << (int)pixel.g << ";" << (int)pixel.b << "m \n"; // Set background color to RGB and output a space
		std::cout << "\033[0m"; // Reset text formatting
	}
	
	// @note drawing the line using slope y-intercept.
	void draw_line(int x1, int y1, int x2, int y2, pixel_t pixel){
		int dx = x2 - x1;
		int dy = y2 - y1;
		float slope = dy / (float)dx;

		for(int x = x1; x <= x2; x++){
			int y = y1 + slope * (x - x1);
			draw_pixel(x, y, pixel);
		}
	}

	void draw_line(const vec2& v1, const vec2& v2, pixel_t pixel){
		// @note computing offset of the x2-x1, y2-y1
		int dx = v2.x - v1.x;
		int dy = v2.y - v1.y;

		float slope = dy / (float)dx;

		for(int x = v1.x; x <= v2.x; x++){
			int y = v1.y + slope * (x - v1.x);
			draw_pixel(x, y, pixel);
		}
	}

	void draw_square(const vec2& v1, size_t width, size_t height, pixel_t pixel){
		int newX = v1.x + width - 1;
		int newY = v1.y + height - 1;

		for(int x = v1.x; x <= newX; x++){
			draw_pixel(x, v1.y, pixel);
			draw_pixel(x, newY, pixel);
		}

		for(int y = v1.y+1; y <= newY; y++){
			draw_pixel(v1.x, y, pixel);
			draw_pixel(newX, y, pixel);
		}
	}

	/* void display(){} */
	void refresh(){
		clearscreen();
	}
private:

	void setCursorPosition(int x, int y){
		std::cout << "\033[" << y << ";" << x << "H";
	}

	//Clears the screen
	inline void clearscreen() {
		std::cerr << "\033[2J";
	}

private:
	BufferType* buffers;
};
