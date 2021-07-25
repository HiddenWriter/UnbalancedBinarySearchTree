#include "pch.h"
int main(void)
{
	std::unique_ptr<App> app = std::make_unique<App>();
	app->Run();
	return 0;
}