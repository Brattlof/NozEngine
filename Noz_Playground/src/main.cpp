#include <Noz.hpp>

int Entry(int argc, char** argv)
{
	std::unique_ptr<Noz::Window> window = std::make_unique<Noz::Window>(NOZ_OBFUSCATE("NOZ_PLAYGROUND"), 900, 600);

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