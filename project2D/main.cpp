#include "Application2D.h"

int main() {
	
	// allocation
	auto app = new Application2D();

	// initialise and loop
	app->run("AIE", 720, 480, false);

	// deallocation
	delete app;

	return 0;
}