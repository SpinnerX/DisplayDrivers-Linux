#pragma once
#include <cstdint>
#include <iomanip>

namespace libhal{
	// @note Contains raw pixel data
	struct pixel_t{
		uint8_t r; // @note red
		uint8_t g; // @note green
		uint8_t b; // @note blue
		uint8_t a; // @note alpha - transparency
	};

	struct coord_t{
		int x;
		int y;
	};

	namespace interfaces{
		

		
		/*
		 * @class Buffer
		 *
		 * @note Interface class that will represent a more generic buffer.
		 * 
		 * @function read(pixel_t);
		 * @note used for reading in a pixel
		 *
		 *
		 *
		 * @function onUpdate()
		 * @param this will be used for updating each frame being displayed by the framebuffer on the display
		 *
		 * @function onRender()
		 * @note used for the rendering process, or this could be the function to call when calling other rendering API's as well.
		 *
		 * @function clear()
		 * @note Will refresh each frame showing the next frame,
		 *
		*/
		class Buffer{
		public:

			virtual bool read(pixel_t& pixel) = 0;

			/* virtual void setPixel(pixel_t pixel) = 0; */

			virtual void setPixel(uint8_t x, uint8_t y, pixel_t) = 0;
			
			virtual void clear() = 0;

			virtual void onUpdate() = 0;

			virtual void onRender() = 0;
			
			static Buffer* read(pixel_t* data, size_t size);

		protected:
			virtual bool transcode() = 0;
		};
			


	}; // end of libhal::interfaces
	
	// @note the idea is that the users may want to create a buffer with data or no data (meaning specifying the size)
	// @note the Idea that I was considering was having some kind of factory/builder function that will build the kind of buffer that we wanted to instantiate our object to
	static interfaces::Buffer* CreateBuffer(std::size_t size);

	static interfaces::Buffer* CreateBuffer(pixel_t* data, size_t size);
}; // end of libhal namespace
