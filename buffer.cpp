#include <cstdint>
#include <iomanip>
#include <cmath>
using namespace std;

/*
 * @note quick visual shown below
 *				T				T -> U			U
 * @visual = [framebuffer] -> [transcode] -> [lcd driver]
 *
*/

/*
 * @file buffer.cpp
 * @note buffer.cpp is going to be more of discussing how buffers are going to be management
 * @note such as working with a single buffer, deciding what if users want to decide to pass in a buffer, or no buffer at all.
 * @note-to-myself in-thought have been considering what if dynamic framebuffers?
 *
 * @topic Buffer Data Management
 * @note this is going to be initially just implementing just a POC idea of how the interfaces can potentially work
 * @note things to consider while doing this are cost in checks, how these calls are going to be made, how data management will work?
 * @note focusing if we have one buffer, then focusing on what if we have multiple buffers, and how this is going to work?
 * 
 * @idea another thing to look into is possibly having a frame buffer layout.
 * @define Is being able to structure how ouw data is going to be stored
 * @note specifics is basically data ortganization such as size, type, order of attributes within the buffers, etc.
 * @note Makes it easier to interpret and process data
 *
 * @note The idea of having a frame buffer layout is that it can format the data however we want.
 * @note what we should be able to do is ask the user the format to specify
 * @note by having the user specify the format 
 *
 *
 * @topic data to be managed (this is just generic data, can decide what to be seperate and data be part of the buffer)
 * @data pos/coordinates
 * @data rgba
 * @config brightness intensity
 * @config hsync
 * @config vsync
 *
 *
 *
 * @topic functions/api calls
 * @function read()
 * @note reading pixels from the frame buffer.
 * @note the idea is that when we send continuous data, we are able to stream data from the frame buffer to the LCD driver.
 *
 * @function send()
 * @note Im thinking we can send raw data the user specified to the framebuffer
 * @note When looking at raw data some things come to mind storage, conditinoing, output of video signals that the driver will send to the display device
 *
 * @function write()
 * @note Now writing I am quite still unsure about how I may want to look into this.
 * @note though I am consider we can write data to a buffer so like: lcdDisplay.write(rgb);
 * @note where in that example if there are rgba channels not used, then potentially have a default value stored for them. (or something but still negotiable)
 * 
*/


/*
 * @topic types of overhead
 * @note looking at the different types of overrhead that can occur with how I am approaching in this.
 * @note overhead for at least how I may be planning in handling framebuffer data
 *
 *
 *
 *
 *
 *
 *
 *
 * */

// @note Per color channels are, r=3by, g=3by, b=3by
// @note If there are transparency channel (a), then will be 4bytes per channel.
// @note These are different ways at approaching how we might want to handle pixel data
struct pixel_t{
	uint16_t rgba;
};

struct pixel_t2{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};


enum class Format_t : uint8_t{
	None = 0,
	RGB,
	RGBA
};

class Framebuffer{
	struct pos{
		int x, y, z;
	};
	
};

template<Format_t F, std::size_t size>
struct BufferLayout{
	
	inline constexpr void* data() const { return (void *)buffer.data(); }

	std::array<pixel_t, size> buffer;
};

// @note just some fake rendering function (so lets assume we do rendering stuff with some API as an FYI
void onRender(void* data){
}


/*
 *
 * @note example of how users can make API calls, and basic API design
 * @note also note of discussion how this'll work on its API's backend as well
 *
*/

int main(){

	// @note just poc for having an idea on how the layout is going to work
	
	// @note lets say that the user was to use our driver for handling a buffer.
	// @note an idea on how the API could be called by specifying the format and size of the buffer
	BufferLayout<Format_t::RGBA, 1024> buffer{};

	onRender(buffer.data());

	return 0;
}
