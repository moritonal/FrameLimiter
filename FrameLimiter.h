#include <thread>
#include <chrono>
#include <iostream>

class FrameLimiter
{
private:
	std::chrono::system_clock::time_point last;
	std::chrono::duration<double> timePerFrame;

	unsigned int frameRate = 0;
	double nextFrameRate = 1.0;

	double desiredFrameRate = 0;

public:
	FrameLimiter(double _frameRate = 60.0)
	{
		this->desiredFrameRate = _frameRate;
		timePerFrame = std::chrono::duration<double>(1.0 / desiredFrameRate);
	}

	double Start()
	{
		auto timePassedInSeconds = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - last).count() * 1.0e-9;
		last = std::chrono::high_resolution_clock::now();

		if (nextFrameRate <= 0)
		{
			nextFrameRate = 1.0;
			std::cout << "Framerate: " << std::to_string(this->frameRate);
			frameRate = 0;
		}
		else
		{
			nextFrameRate -= timePassedInSeconds;
			frameRate++;
		}

		return timePassedInSeconds;
	}

	void End()
	{
		std::chrono::duration<double> timePassed = std::chrono::high_resolution_clock::now() - last;
		auto timeToSleep = std::chrono::duration_cast<std::chrono::nanoseconds>(this->timePerFrame - timePassed);

		std::this_thread::sleep_for(timeToSleep);
	}
};