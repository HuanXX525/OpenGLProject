#include<glad.h>
#include<iostream>
#include<mylib/FrameBuffer.h>
#include<spdlog/spdlog.h>
FrameBuffer::FrameBuffer(uint32_t width, uint32_t height) :width(width), height(height) {
	Invaidate();
}

FrameBuffer::~FrameBuffer() {
	//glDeleteFramebuffers(1, &frameBufferID);
	Release(&frameBufferID, &colorAttachment, &depth_StencilAttachment);
}



void FrameBuffer::Release(unsigned int* fb, unsigned int* ca, unsigned int* dsa) {
	if (*fb) {
		glDeleteFramebuffers(1, fb);
		*fb = 0;
	}
	if (*ca) {
		glDeleteTextures(1, ca);
		*ca = 0;
	}
	if (*dsa) {
		glDeleteTextures(1, dsa);
		*dsa = 0;
	}
}

void FrameBuffer::Invaidate() {
	//创建缓冲区
	glGenFramebuffers(1, &frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	//生成三颜色通道纹理
	glGenTextures(1, &colorAttachment);
	glBindTexture(GL_TEXTURE_2D, colorAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr); // 加载GL_RGBA格式的纹理到GL_RGBA8，并分配一个内存
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 纹理过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//生成对应的颜色缓冲区
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment, 0);
	//生成深度纹理
	glGenTextures(1, &depth_StencilAttachment);
	glBindTexture(GL_TEXTURE_2D, depth_StencilAttachment);
	//glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Width, m_Height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
	//生成深度缓冲区
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depth_StencilAttachment, 0);
	if (!(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE))
		spdlog::error("Frame Buffer Config Error");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Resize(uint32_t width, uint32_t height) {
	// 窗口大小改变，重新设置缓冲区
	this->width = width;
	this->height = height;
	unsigned int tfa, tca, tdsa;
	tfa = frameBufferID; // 缓存旧帧
	tca = colorAttachment; 
	tdsa = depth_StencilAttachment;
	Invaidate();
	Release(&tfa, &tca, &tdsa); // 释放旧帧
}

void FrameBuffer::Bind() {
	// 绑定到自定义的帧缓冲区
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
}

void FrameBuffer::UBind() {
	// 解绑帧缓冲区，绑定到默认缓冲区
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
