#include <FrameLimiter.h>

int main()
{
	//Setup FrameLimiter @ 60fps
	FrameLimiter updateFrameLimiter(60);

	while (true)
	{
		//Get time-passed
		double timePassedInSeconds = updateFrameLimiter.Start();

		//Perform function
		std::this_thread::sleep_for(std::chrono::milliseconds(2));

		//Sync up with intended frame-rate
		updateFrameLimiter.End();
	}
}