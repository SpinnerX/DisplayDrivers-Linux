#pragma once
#include <array>
#include <cstdint>
#include <iostream>
#include <initializer_list>

struct pixel_t{
	uint8_t r, g, b, a;
};

struct vec2{
	int x=0, y=0;
};

enum class Validation : uint8_t {
	DEFAULT,
	HAL_GOOD,
	HAL_INVALID
};

template<size_t Width, size_t Height>
struct Colorbuffer{
	
	pixel_t get(int x, int y){
		return buffer[y * Width + x];
	}

	std::array<pixel_t, Width * Height> buffer;
};



template<typename T, auto SIZE>
struct Indexbuffer{
	Indexbuffer(const std::initializer_list<T>&& list) : indices(list){}
	
	void* data() const {
		return indices.data();
	}

	std::array<uint8_t, SIZE> indices;
};

template<size_t Width, size_t Height>
struct Framebuffer{
	
	/* template<typename T, typename... Args> */
	/* Framebuffer(const std::initializer_list<T> list) { */
	/* 	std::array<T, Width * Height> array(list); */
	/* } */

	uint8_t* data() { return vertices.data(); }

	size_t width() const { return Width; }

	size_t height() const { return Height; }

	std::array<pixel_t, Width * Height> vertices;

};

template<typename BufferType>
class DisplayDriver{
public:
	DisplayDriver(BufferType& buffer) : buffers(&buffer){}
	
	// @note Clearing the color buffer
	// @note these values are going to be clamped from range [0, 1]
	void setClearColor(uint8_t r, uint8_t g, uint8_t b){
		clearscreen();
		draw_pixel(0, 0, {r, g, b});
	}
	
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
	
	// @note considering creating a draw call for handling taking in a buffer.
	// @note considering potentially making this a void* to take in any kinds of data, but still deciding.
	// @note idea in passing a buffer is the user should be able to draw and pass in through a draw call the buffer of data they want to draw.
	// @note rather then setting up values then drawing, just pass in the buffer containing data (pixels, position, etc.) then drawing that
	// @note eventually we may utilize render commands for sending commands to the display for this, but for now. This is how its going to work
	// @note until I get a better idea in how I want to do this.
	void draw(const vec2& v, BufferType& buffer){}

	// @note refreshing the screen (at least in the terminal.
	// @note for now all this'll do is use clearscreen()
	// @note Though this may have actual use once, I can see how this is going to work.
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
