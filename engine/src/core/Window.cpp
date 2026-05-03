#define GLFW_INCLUDE_NONE
#include "Window.h"
#include <glad/gl.h>
#include <spdlog/spdlog.h>

namespace game {
	window::win	dow(int width, int height, const std::string& title) : width_(width), height_(height), handle_(nullptr) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

		handle_ = glfwCreateWindow(width_, height_, title.c_str(), NULL, NULL);
		
		if (!handle_) {
			spdlog::error("Can't create window \n");
		}

		glfwMakeContextCurrent(handle_);
	}

	window::~window() {
		if (!handle) {
			glfwDestroyWindow(handle_);
		}
	}
}

static void error_callback(int error, const char* description) {
	spdlog::error("GLFW Error [{}]: {}", error, description);
}

int main() {
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) exit(EXIT_FAILURE);


	game::window myWindow(1280, 720, "Voxel Engine");

	if (!myWindow.isOK()) exit(EXIT_FAILURE);

	while (!glfwWindowShouldClose(myWindow.getHandle())) {
		glfwSwapBuffers(myWindow.getHandle());
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}