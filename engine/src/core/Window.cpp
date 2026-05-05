#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include "Window.h"
#include "Logger.h"
#include <spdlog/spdlog.h>

static void error_callback(int error, const char* description) {
	Logger::error("GLFW Error [{}]: {}", error, description);
}

namespace game {
	bool window::init() {
		glfwSetErrorCallback(error_callback);
		return glfwInit() != GLFW_FALSE;
	}

	void window::shutdown() {
		glfwTerminate();
	}

	window::window(int width, int height, const std::string& title) : width_(width), height_(height), handle_(nullptr) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		handle_ = glfwCreateWindow(width_, height_, title.c_str(), NULL, NULL);

		if (!handle_) {
			Logger::error("Can't create window \n");
			return;
		}

		glfwMakeContextCurrent(handle_);

		int version = gladLoadGL((GLADloadfunc)glfwGetProcAddress);
		if (version == 0) {
			Logger::error("Failed to initialize OpenGL context");
		}
		int major, minor = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);
		Logger::info("Wersja OpenGL: {}.{}", major, minor);

	}

	window::~window() {
		if (handle_) {
			glfwDestroyWindow(handle_);
		}
	}

	bool window::shouldClose() const {
		return glfwWindowShouldClose(handle_);
	}

	void window::pollEvents() {
		glfwPollEvents();
	}

	void window::swapBuffers() {
		glfwSwapBuffers(handle_);
	}
}

