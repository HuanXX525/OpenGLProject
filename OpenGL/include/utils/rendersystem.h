#pragma once
#ifndef MYLIB_RENDERSYSTEM_H
#define MYLIB_RENDERSYSTEM_H
#include <iostream>
#include <imgui/imgui.h>
#include <utils/top.h>
#include <utils/FrameBuffer.h>

class RenderWindow : public Windows {
private:
	std::chrono::steady_clock::time_point resizeTimeStart; // 用于渲染窗口更新
    ImVec2 viewPortSize = ImVec2(640.0f, 480.0f);
    ImVec2 lastViewPortSize = ImVec2(640.0f, 480.0f);
    FrameBuffer* pFrameBuffer;
    float refreshTime = 0.3f;
public:
	static RenderWindow* Instance() {
		return new RenderWindow();
	}

    void Init(FrameBuffer* pFrameBuffer) {
        this->pFrameBuffer = pFrameBuffer;
    }

	void Draw(const char* name, bool* isOpen) {
		if (ImGui::Begin(name, isOpen)) {
            //获取ViewPort窗口的大小
            viewPortSize = ImGui::GetContentRegionAvail();
            //ViewPort窗口大小如果有改变，那么需要重置帧缓冲区
            //spdlog::info("{}", viewPortSize.x == lastViewPortSize.x);
            if ((viewPortSize.x != lastViewPortSize.x || viewPortSize.y != lastViewPortSize.y)) {
                resizeTimeStart = std::chrono::high_resolution_clock::now(); // for timing
            }
            if ((viewPortSize.x != pFrameBuffer->GetWidth() || viewPortSize.y != pFrameBuffer->GetHeight())) {
                auto resizeTimeEnd = std::chrono::high_resolution_clock::now(); // for timing
                double elapsedTime = std::chrono::duration<double>(resizeTimeEnd - resizeTimeStart).count();
                //spdlog::info("{}", elapsedTime);
                if (elapsedTime > refreshTime) {
                    glViewport(0, 0, (GLsizei)viewPortSize.x, (GLsizei)viewPortSize.y);
                    pFrameBuffer->Resize((GLsizei)viewPortSize.x, (GLsizei)viewPortSize.y);
                }
            }
            lastViewPortSize = viewPortSize;
            //获取颜色纹理的ID
            unsigned int textureID = pFrameBuffer->GetColorAttachment();
            ImGui::Image(textureID, viewPortSize, { 0,1 }, { 1,0 });

		}
		ImGui::End();
	}

	~RenderWindow() override {
        //delete(pFrameBuffer);
	}
};

#endif // !MYLIB_RENDERSYSTEM_H
