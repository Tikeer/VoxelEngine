#include <spdlog/spdlog.h>
#include "Window.h"

int main() {
	if (!game::window::init()) return -1;	

	game::window myWindow(1280, 720, "Voxel Engine");
	if (!myWindow.isOK()) return -1;

	while (!myWindow.shouldClose()) {
		myWindow.swapBuffers();
		myWindow.pollEvents();
	}
		
	game::window::shutdown();
	return 0;
}