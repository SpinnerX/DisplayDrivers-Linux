#include <cstdint>
#include <iomanip>
#include <cmath>
using namespace std;


/*
 * @file display.cpp
 * @note display.cpp is just going to be a discussion relatively to how we are going to be passing the data
 * @note including user interaction and how they'll pass this data to the display
 * @note-to-self there might be some duplicated stuff, but its to seperate the two thought processes in terms of buffer.
 * @note this is in the scenario that when trying to think of a way of how we want to pass data to the user is going to work with displays.
 * @note Adding context further in how the buffer is pass data to displays
 * @note Looking into a POC of how to work with generic LCD's, whether we are starting with one atm.
 * @note that is what Display.cpp is going to cover
 *
 * @topic user interaction with buffer(BufferLayout) and passing to display drivers
 * @topic display drivers design and some choices to look into while doing so.
 *
 *
 *
 *
*/

// @note reference to buffer.cpp for more info the buffer/data related topics
// @note especially for pixel_t, framebuffer, and buffer layouts.
struct pixel_t{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};





enum class Format_t : uint8_t {
	None = 0,
	RGB,
	RGBA
};


struct Framebuffer{
	struct pos{
		int x, y, z;
	};
};


template<Format_t F, std::size_t SIZE>
struct BufferLayout{

	std::array<pixel_t, SIZE> pixelBuffers;
	std::array<Framebuffer, SIZE> framebuffers;
};


/*
 * @topic Display classes
 * @function onUpdate()
 * @function setPixel()
 * @param BufferLayout
 *
*/

// @note one other way to looking into this
// @note potentially utilizing Khalil's exceptions stuff...
struct DisplayFormatNotFound : public std::exception{
	std::error_code error;
};

template<Format_t F>
class Display0{
public:
	Display0<F>(){}

	virtual void setPixel(pixel_t data) = 0;

	virtual void onUpdate() = 0;

	BufferLayout<F, 1024> bufferLayouts;
};

class DisplayLcdRgb0 : public Display0<Format_t::RGB>{
public:
	DisplayLcdRgb0() = default;

	virtual void setPixel(pixel_t data) override{}

	virtual void onUpdate() override {}
};

template<Format_t F>
Display0<F>* CreateDisplayDriver(){
	switch (F) {
		case Format_t::RGB:
			return new DisplayLcdRgb0();
		case Format_t::RGBA: break;
		default:
			throw DisplayFormatNotFound(); // @note just some fake exception (lol)
	}
}


// @note here is my second idea on how we can find some kind of way in handling different generic display formats 

class Display{
public:
	virtual void setPixel(pixel_t pixel) = 0;

	virtual void onUpdate() = 0;
};


class DisplayLcdRgb : public Display{
public:

	virtual void setPixel(pixel_t pixel) override{
	}

	virtual void onUpdate() override{
		
	}
};

static Display* CreateDisplayDriver(Format_t format){
	switch (format) {
	case Format_t::RGB:
		return new DisplayLcdRgb();
	case Format_t::RGBA:
		break;
	default:
		break;
	}

	return nullptr;
}

/*
 *
 * @note example of how we may want users to call our API's
 * 
 * DisplayLcdScreenRgba = CreateDisplayDriver<RGB>(buffer);
 * 
 * 
*/

int main(){
}
