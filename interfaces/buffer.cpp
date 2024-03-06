#include "buffer.h"
#include <iomanip>
#include <type_traits>
#include <concepts>

template<typename T, auto VAR>
struct Wrapper {
    static constexpr auto value = VAR;
    constexpr operator decltype(value)() const {
        return value;
    }
};


template<size_t Width, size_t Height>
struct FrameBuffer{
	FrameBuffer() = default;
	/* FrameBuffer(size_t w, size_t h) {} */
	void draw_pixel(int x, int y, pixel_t pixel){}

	std::array<pixel_t, Width * Height> data;
};

DisplayDriver::DisplayDriver(void* data) : framebuffer(data) {}

