#pragma once
#include <GLFW/glfw3.h>
#include <string>


namespace game {
	class window {
	private:
		int height_;
		int width_;
		GLFWwindow* handle_;

	public:
		window(int height, int width, const std::string& title);
		~window();

		bool isOK() const {
			return handle_ != nullptr;
		}

		GLFWwindow* getHandle() {
			return handle_;
		};
	}
}