
#ifdef __cplusplus

#ifndef __FRAMEBUFFER_LIB_H__
#define __FRAMEBUFFER_LIB_H__

/**
 * @file FrameBuffer.hpp
 * @brief Frame-buffer primitives used by the ILI9341 driver.
 */

#include <cstdint>
#include <string>
#include "font/fonts.hpp"
#include "main.h"

namespace TFT_LCD {
    /**
     * @brief RGB565 pixel container.
     */
    union Pixel{
        /** @brief Packed RGB565 pixel value. */
        uint16_t value;

        /** @brief Bit-field view of RGB565 color channels. */
        struct {
            uint16_t blue  : 5;
            uint16_t green : 6;
            uint16_t red   : 5;
        } color;

        /** @brief Construct black pixel (0x0000). */
        Pixel() : value{0} {}
        /** @brief Construct from packed RGB565 value. */
        Pixel(uint16_t val) : value{val} {}
        /** @brief Construct from RGB565 channel values. */
        Pixel(uint8_t blue, uint8_t green, uint8_t red) :
            color{.blue = blue, .green = green, .red = red} {}

        /** @brief Implicit conversion to packed RGB565 value. */
        operator uint16_t() const {
            return value;
        }
    };

    /**
     * @brief 2D RGB565 frame-buffer utility.
     */
    class FrameBuffer{
    public:
        /** @brief Pixel storage format identifier used by the copy path. */
        enum PixelFormat : uint8_t{
            RGB565  = 2
        };

    private:
        Pixel* _buffer = nullptr;
        uint32_t _width = 0;
        uint32_t _height = 0;
        uint32_t _pixelFormat = 0;
        
    public:
        FrameBuffer() = default;
        /**
         * @brief Construct frame buffer from raw RGB565 memory.
         * @param buffer Base address of RGB565 pixels.
         * @param width Frame width in pixels.
         * @param height Frame height in pixels.
         * @param format Pixel storage format.
         */
        explicit FrameBuffer(uint16_t* const buffer, uint32_t width, uint32_t height,PixelFormat format = RGB565);

        /**
         * @brief Assign descriptor values from another frame buffer.
         * @param other Source descriptor.
         * @return Reference to this object.
         */
        FrameBuffer& operator=(const FrameBuffer& other);

        /**
         * @brief Replace underlying pixel buffer pointer.
         * @param newBuffer New pixel buffer base address.
         */
        void setBuffer(Pixel* const newBuffer);

        /**
         * @brief Get raw frame-buffer address.
         * @return Pointer to underlying pixel memory.
         */
        void* getBufferAddress() const {
            return _buffer;
        }

        /**
         * @brief Access a pixel by coordinates.
         * @param x X coordinate.
         * @param y Y coordinate.
         * @return Reference to pixel at `(x, y)`.
         */
        Pixel& at(uint32_t x, uint32_t y);
        /**
         * @brief Get frame width in pixels.
         * @return Width in pixels.
         */
        uint32_t getWidth() const;

        /**
         * @brief Set frame width.
         * @param width Width in pixels.
         */
        void setWidth(uint32_t width);

        /**
         * @brief Get frame height in pixels.
         * @return Height in pixels.
         */
        uint32_t getHeight() const;

        /**
         * @brief Set frame height.
         * @param height Height in pixels.
         */
        void setHeight(uint32_t height);

        /**
         * @brief Copy full frame from another buffer.
         * @param other Source frame buffer.
         * @param hdma2d Optional DMA2D handle. If null, `memcpy` is used.
         */
        void copyBuffer(FrameBuffer& other,DMA2D_HandleTypeDef * hdma2d = nullptr);

        /**
         * @brief Draw a filled rectangle.
         * @param x Left pixel coordinate.
         * @param y Top pixel coordinate.
         * @param width Rectangle width in pixels.
         * @param height Rectangle height in pixels.
         * @param color Fill color.
         */
        void drawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Pixel color);

        /**
         * @brief Draw a text string.
         * @param text Text to render.
         * @param x Left pixel coordinate.
         * @param y Top pixel coordinate.
         * @param font Font descriptor.
         * @param color Glyph color.
         */
        void putText(std::string text, uint32_t x,uint32_t y,const sFONT& font,Pixel color);
        /**
         * @brief Draw a single character.
         * @param character ASCII character code.
         * @param x Left pixel coordinate.
         * @param y Top pixel coordinate.
         * @param font Font descriptor.
         * @param color Glyph color.
         */
        void putChar(uint8_t character,uint32_t x,uint32_t y,const sFONT& font,Pixel color);
    };
}

#endif // __FRAMEBUFFER_LIB_H__

#endif // __cplusplus
