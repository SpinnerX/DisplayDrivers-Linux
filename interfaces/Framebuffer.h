#pragma once
#include "buffer.h"
#include <array>

namespace libhal{
	
	/*
	 *
	 * @class Framebuffer
	 * @note contains raw pixel data
	 *
	 *
	 *
	 *
	 * */
	template<std::size_t width, size_t height>
	class Framebuffer : public interfaces::Buffer{
	public:
		Framebuffer() = default;

		virtual bool read(pixel_t& pixel) override { return true; }
		
		virtual void setPixel(uint8_t x, uint8_t y, pixel_t pixel){
			frames[x * width * y] = pixel;
		}

		virtual void setPixel(uint8_t r, uint8_t g, uint8_t b){}

		virtual void onUpdate() override{}
		
		virtual onRender() override {}

		virtual void clear() override{}

	protected:

		// @function transcode()
		// @note Color Space Conversion
		// @note Converting raw pixel data between different colorspaces such as RGB to YUBV, CMYK, etc
		// @note Pixel Format Conversion
		// @note converting pixel data between different pixel formats varying in color depth
		// @note Gamma Correction
		// @note Adjusting pixel intensity
		virtual bool transcode() override{}

	private:
		std::array<pixel_t, width * height> frames;
	};
};
