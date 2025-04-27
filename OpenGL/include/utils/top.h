#pragma once
#ifndef MYLIB_TOP_H
#define MYLIB_TOP_H
#include <iostream>
#include <chrono>
#include <imgui/imgui.h>
#ifdef _WIN32
#include <Windows.h>
std::wstring Utf8ToWide(const std::string& utf8Str);
std::string GBKToUTF8(const std::string& gbkStr);
std::string UTF8ToANSI(const std::string& utf8Str);
#endif
// 输出文字到IMGUI
void Error(std::string str);
void SubInfo(std::string str);
void Info(std::string str);
// 输出文字到IMGUI
// 将 UTF-8 字符串转换为宽字符字符串


class Windows {
	public:
	virtual void Draw(const char* name, bool* isOpen) = 0;
	virtual ~Windows() = 0;
};

 inline Windows::~Windows() {
	// 这里可以添加基类需要释放资源的代码
	std::cout << "Windows release" << std::endl;
}

class FrameRate {
private:
	std::chrono::steady_clock::time_point lastFrameTime; // 上一次的时间
public:
	float calculateFPS() {
		auto currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<float> elapsedTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;
		// 计算帧率
		return 1.0f / elapsedTime.count();
	}
};



#endif
