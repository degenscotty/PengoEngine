#include "pch.h"
#include "Application.h"
#include <vld.h>

#define SDL_MAIN_HANDLED

extern Application* CreateApplication();

#undef main

int main(int argc, char* argv[])
{
	Log::Init();

	auto app = CreateApplication();
	app->Run();
	delete app;

	return 0;
}