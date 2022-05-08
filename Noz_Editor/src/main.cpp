#include <Noz.hpp>

// Supposed to be the editor later on

int Entry(int argc, char** argv)
{
	std::unique_ptr<Noz::Application> app = std::make_unique<Noz::Application>(NOZ_OBFUSCATE("NOZ_PLAYGROUND"), 900, 600);

	while (app->Run())
	{
		
	}

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