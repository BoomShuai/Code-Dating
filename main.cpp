#include "Window.h"

int main()
{

	Window window(GetSystemMetrics(SM_CYSCREEN), GetSystemMetrics(SM_CYSCREEN));
	window.show();
	window.messageLoop();
	return 0;
}