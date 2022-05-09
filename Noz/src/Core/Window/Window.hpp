#pragma once

#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>

#ifdef BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32

#elif defined BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#define GLFW_EXPOSE_NATIVE_X11

#elif defined BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

struct PosColorVertex
{
    float x;
    float y;
    float z;
    uint32_t abgr;
};
static PosColorVertex cubeVertices[] =
{
    {-1.0f,  1.0f,  1.0f, 0xff888888 },
    { 1.0f,  1.0f,  1.0f, 0xff8888ff },
    {-1.0f, -1.0f,  1.0f, 0xff88ff88 },
    { 1.0f, -1.0f,  1.0f, 0xff88ffff },
    {-1.0f,  1.0f, -1.0f, 0xffff8888 },
    { 1.0f,  1.0f, -1.0f, 0xffff88ff },
    {-1.0f, -1.0f, -1.0f, 0xffffff88 },
    { 1.0f, -1.0f, -1.0f, 0xffffffff },
};
static const uint16_t cubeTriList[] =
{
    0, 1, 2,
    1, 3, 2,
    4, 6, 5,
    5, 6, 7,
    0, 2, 4,
    4, 2, 6,
    1, 5, 3,
    5, 7, 3,
    0, 4, 1,
    4, 5, 1,
    2, 3, 6,
    6, 3, 7,
};

#include <GLFW/glfw3native.h>

namespace Noz
{
	class Window
	{
	private:
		const char* m_Title;
		int m_Width, m_Height;
		GLFWwindow* m_Window;

	public:
		Window(const char* title, int width, int height, bool use_imgui = false);
		~Window();

		void Update();

		bool Setup(const char* title, int width, int height, bool use_imgui);
		void Cleanup();
		bool Alive();
	};
}