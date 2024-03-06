#pragma once
#include <cstdint>
#include <iomanip>
#include <array>

/*
 * @notes
 * @note Utilizing templates allow the compiler to know what buffer is being passed into
 * @note Allowing to know about the buffer type we are passing, thus the functions we are calling
 *
 *
 * @note Here is a few things to note about virtual functions
 * @note Using pure virtual functions will basically expand the vtable
 * @note And this is probably something to consider when deciding the virtual functions.
 * @note Keep in mind, that using virtual functions only if you know you are going to
 *		 minimize the function calls to these virtual functions.
 *
 *
 *
 *
 * Questions
 * @question Look at the limitations of the following implementations below?
 * @question Because the issue with this implementation is that it is header-only.
 * @note which means that you wont be able to hide implementations details.
 *
 *
 *
 * Design Notes and Considerations
 * @note when designing how the display drivers are going to work
 * @note 
 *
 *
 *
 * Functions API calls.
 * @note Consider the limitations of the following paradigms before continuing
 * @note Considering such as that what are other paradigms that we can look into.
 * @function draw_pixel(x, y, pixel)
 * @note used for drawing the pixels using the pixels 
 *
 *
 * Notes about Different paradigms and questions ask myself.
 * @question What are limitations that you can see with that paradigm (like templates)
 * @note Limitations using templates as an example are templates are header-only
 * @note Another example is limitations with virtual functions because if there
 *		 are going to be many calls to it will expand it's vtable.
 * @note Only consider virtual functions or classes if you know that the minimal times the function will be called is
 *		 going to be at a minimum. (Like once or twice)
 *
 *
 *
 * @question I am seeing that some LCD Controller Interfaces, how come some use the communication protocols?
 * @note Meaning that they are interfacing with displays but also interfacing with another communication protocols.
 *
 * @idea An idea is what if you have a Larger enough buffers and not enough memory,
 *		 to hold this large buffer
 * @example An example is lets say you have a 1024x1024 buffer, and you only have 64kb of memory.
 *			You would essentially grab the first 64kb small buffer and render that to the top-left of the screen
 *			and iterate throughout the screen. Initially iterating 64kb across the screen.
 *
 *	@note Look into embedded graphics libraries, and embedded Qt on how we can tackle this problem
 *	@note because there are issues such as vtable expansion using virtual function/classes.
 *	
 *	Some more Ideas 
 *	@note Getting the pointer to the driver
 *
 *	@CHECK
 *	@note Using Objdump and check the assembly
 *	@note Checking if the objects that we are calling get inlined.
 *	@note If they aren't getting inlined that will be brought up in discussion
 *	@note But first get something working and the application, and then test that out with raw RGBA values.
*/


struct pixel_t{
	uint8_t r, g, b, a;
};

template<size_t Width, size_t Height>
struct GrayscaleBuffer{
  std::array<std::uint8_t, Width * Height> data;

  void draw_pixel(int x, int y, pixel_t pixel){
    if (0 <= x and x <= Width and 0 <= y and y < Height) {
		/* data[x][y] = (pixel.r + pixel.g + pixel.b + pixel.a) / 4; */
		data[x * Height * y] = (pixel.r + pixel.g + pixel.b + pixel.a) / 4;
	}
  }
};

template<typename Buffer>
class Graphics{
public:
  Graphics(Buffer& p_buffer)
    : m_buffer(&p_buffer){}

  void square(int x, int y, int width, int height)
  {
    /* m_buffer.draw_pixel(...); */
  }
  template<int x, int y, int width, int height>
  void square()
  {
    m_buffer.draw_pixel(/*...*/);
  }

private:
  Buffer* m_buffer;
};

void draw_thing(){
  GrayscaleBuffer<128, 64> my_buffer{};
  Graphics my_graphic(my_buffer);
  my_graphic.square(0, 0, 50, 12);
}
