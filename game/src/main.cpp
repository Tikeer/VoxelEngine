#include <spdlog/spdlog.h>
#include "Window.h"

int main() {
	if (!game::window::init()) return -1;	

	game::window myWindow(1920, 1080, "Voxel Engine v0.0.1");
	if (!myWindow.isOK()) return -1;

	while (!myWindow.shouldClose()) {
		myWindow.swapBuffers();
		myWindow.pollEvents();
	}
		
	game::window::shutdown();
	return 0;
}