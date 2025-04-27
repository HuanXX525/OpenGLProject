/*****************************************************************//**
 * \file   bar.h
 * \brief  定义了顶部菜单栏和底部状态栏以及集中窗口的管理
 * 若想要添加窗口，可按照以下步骤
 * 1、创建窗口类并继承top.h下的Windows类
 * 2、修改WINDOW_NUM的数量
 * 3、在枚举Window添加你的窗口
 * 4、添加UI到WINDOW子菜单
 * 5、如果有窗口初始化需要，在InitWindows函数初始化
 * 
 * \author Administrator
 * \date   March 2025
 *********************************************************************/
#pragma once
#ifndef MYLIB_BAR_H
#define MYLIB_BAR_H
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <mylib/top.h>
#include <mylib/filesystem.h>
#include <mylib/rendersystem.h>
#define WINDOW_NUM 4 // 实际窗口数量加1

namespace Engine {
	enum Window
	{
		FileManager_ID = 1, PropertyWindow_ID, RenderWindow_ID
	};

	Windows* WinPtrArray[WINDOW_NUM] = { 0 };
	bool WindowsOpen[WINDOW_NUM] = { 0 };
	//bool WindowsCleared[WINDOW_NUM];

	std::string windowName[WINDOW_NUM] = { "", "File Manager", "Property View", "Render Window"};
	void WindowMenuItem(int type, Windows* ptr);
	class MainMenuBar
	{
		GLFWwindow* window;

	public:
		static MainMenuBar* Instance() {
			static MainMenuBar mmb;
			return &mmb;
		}

		void Init(GLFWwindow* win) {
			window = win;
		}

		void Draw() {
			if (ImGui::BeginMainMenuBar()) {
				// Engine
				if (ImGui::BeginMenu("Engine")) {
					if (ImGui::MenuItem("Exit")) {
						glfwSetWindowShouldClose(window, true);
					}
					ImGui::EndMenu();
				}
				// File
				if (ImGui::BeginMenu("File")) {
					if (ImGui::BeginMenu("Import")) {
						if (ImGui::MenuItem(".obj")) {

						}
						ImGui::EndMenu();
					}
					ImGui::EndMenu();
				}
				// Window
				if (ImGui::BeginMenu("Window")) {
					WindowMenuItem(Window::FileManager_ID, FileWindow::Instance());
					WindowMenuItem(Window::PropertyWindow_ID, PropertyWindow::Instance());
					WindowMenuItem(Window::RenderWindow_ID, RenderWindow::Instance());
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}
		}
	};
	class MainBottomBar {
	private:
		//GLFWwindow* window;
		FrameRate frameRate = FrameRate();

	public:
		static MainBottomBar* Instance() {
			static MainBottomBar mmb;
			return &mmb;
		}

		void Init(GLFWwindow* win) {
			//window = win;

		}

		void Draw() {
			ImGuiViewportP* viewport = (ImGuiViewportP*)(void*)ImGui::GetMainViewport();
			if (ImGui::BeginViewportSideBar("##MainStatusBar", viewport, ImGuiDir_Down, 20, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar)) {
				if (ImGui::BeginMenuBar()) {
					ImGui::Text("FPS:%.3f", frameRate.calculateFPS());
					ImGui::EndMenuBar();
				}
			}
				ImGui::End();
		}
	};
	void ClearWindows() {
		for (int i = 1; i < WINDOW_NUM; i++) {
			if (WinPtrArray[i] && !WindowsOpen[i]) { // 窗口关闭并且还没有清理就清理
				delete(WinPtrArray[i]);
				WinPtrArray[i] = NULL;
				//WindowsCleared[i] = true;
			}
		}
	}

	void InitWindows(std::string projectPath, FrameBuffer* pFrameBuffer) {
		for (int i = 1; i < WINDOW_NUM; i++) {
			Windows* currentWin = WinPtrArray[i];
			if (currentWin) {
				switch (i) {
				case Window::FileManager_ID:
					((FileWindow*)currentWin)->Init((PropertyWindow*)WinPtrArray[Window::PropertyWindow_ID]);
					break;
				case Window::PropertyWindow_ID:
					((PropertyWindow*)currentWin)->Init(projectPath);
					break;
				case Window::RenderWindow_ID:
					((RenderWindow*)currentWin)->Init(pFrameBuffer);
					break;
				}
			}
		}
	}

	void DrawWindows() {
		for (int i = 1; i < WINDOW_NUM; i++) {
			if (WinPtrArray[i]) {
				WinPtrArray[i]->Draw(windowName[i].c_str(), &WindowsOpen[i]);
			}
		}
	}

	void WindowMenuItem(int type, Windows* ptr) {
		if (ImGui::MenuItem(windowName[type].c_str())) {
			if (!WindowsOpen[type]) {
				WinPtrArray[type] = ptr;
				WindowsOpen[type] = true; // 打开窗口
			}
		}
	}

	void OpenWindow(int type, Windows* ptr) {
		WinPtrArray[type] = ptr;
		WindowsOpen[type] = true; // 打开窗口
	}


	void OutOfCirInit() {
		// 打开一些基本窗口
		OpenWindow(Window::FileManager_ID, FileWindow::Instance());
		OpenWindow(Window::PropertyWindow_ID, PropertyWindow::Instance()); 
		//OpenWindow(Window::RenderWindow_ID, RenderWindow::Instance()); 
		//std::fill(WindowsCleared, WindowsCleared + WINDOW_NUM, true);
	}
}

#endif // !MYLIB_BAR_H
