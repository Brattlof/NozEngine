#include <Noz.hpp>

int Entry(int argc, char** argv)
{
	Noz::Application* app = new Noz::Application(NOZ_OBFUSCATE("NOZ_PLAYGROUND"), 900, 600);

	while (app->Alive())
	{
		app->Update();
	}

	delete app;

	return 0;
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow)
{
	return Entry(__argc, __argv);
}

int main(int argc, char** argv)
{
	return Entry(argc, argv);
}