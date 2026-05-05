class Time {
private:
	double prevFrame;
	double currentFrame;
	double deltaTime;
	double acumulator;
	double FPS;
	double const fixedStep = 1.0 / 20.0;
public:
	
	void init() {
		prevFrame = glfwGetTime();
	}

	void tick() {
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - prevFrame;
		prevFrame = currentFrame;

		if (deltaTime > 0.25) {
			deltaTime = 0.25;
		}

		acumulator += deltaTime;
		FPS = 1.0 / deltaTime;
	}

	double getDT() {
		return deltaTime;
	}

	double getAcu() {
		return acumulator;
	}

	double getStep() {
		return fixedStep;
	}
};