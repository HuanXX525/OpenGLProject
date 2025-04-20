#pragma once
#include <cstdint>
#ifndef MYLIB_FRAMEBUFFER_H
#define MYLIB_FRAMEBUFFER_H



class FrameBuffer {

public:
	FrameBuffer(uint32_t width, uint32_t height);
	~FrameBuffer();
	void Invaidate();
	void Resize(uint32_t width, uint32_t height);
	inline uint32_t GetWidth() const { return width; }
	inline uint32_t GetHeight() const { return height; }
	inline uint32_t GetColorAttachment() const { return colorAttachment; }

	void Bind();
	void UBind();
private:
	unsigned int frameBufferID, colorAttachment, depth_StencilAttachment;
	unsigned int width, height;
	void Release(unsigned int* fb, unsigned int* ca, unsigned int* dsa);
};

#endif // !MYLIB_FRAMEBUFFER_H
