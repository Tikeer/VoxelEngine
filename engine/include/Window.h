#pragma once
#include <string>
struct GLFWwindow;


namespace game {
	class window {
	private:
		int height_;
		int width_;
		GLFWwindow* handle_;

	public:
		window(int width, int height, const std::string& title);
		~window();

		static bool init();
		static void shutdown();
		bool shouldClose() const;
		void swapBuffers();
		void pollEvents();

		bool isOK() const {
			return handle_ != nullptr;
		}

		GLFWwindow* getHandle() {
			return handle_;
		};
	};
}