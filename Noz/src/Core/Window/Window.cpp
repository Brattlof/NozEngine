#include "pch.hpp"
#include "Window.hpp"
#include <Core/FileManager/FileManager.hpp>

using namespace Noz;

static bgfx::VertexLayout pcvDecl;
static bgfx::VertexBufferHandle vbh;
static bgfx::IndexBufferHandle ibh;
static bgfx::ProgramHandle program;
static unsigned int counter = 0;

static int old_with, old_height;

Window::Window(const char* title, int width, int height, bool use_imgui) :
	m_Title(title),
	m_Width(width),
	m_Height(height)
{
	if (!Setup(title, width, height, use_imgui))
	{
		NOZ_LOG_ERROR(NOZ_OBFUSCATE("Failed to setup window"));
		Cleanup();
	}

	NOZ_LOG_INFO(NOZ_OBFUSCATE("Window setup successful"));
}

Window::~Window()
{
	Cleanup();
}

void Window::Update()
{
	const bx::Vec3 at = { 0.0f, 0.0f,  0.0f };
	const bx::Vec3 eye = { 0.0f, 0.0f, -5.0f };

	float view[16];
	bx::mtxLookAt(view, eye, at);

	float proj[16];
	bx::mtxProj(proj, 60.0f, float(m_Width) / float(m_Height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
	bgfx::setViewTransform(0, view, proj);

	float mtx[16];
	bx::mtxRotateXY(mtx, counter * 0.01f, counter * 0.0081f);

	bgfx::touch(0);

	bgfx::setTransform(mtx);
	bgfx::setVertexBuffer(0, vbh);
	bgfx::setIndexBuffer(ibh);
	bgfx::setDebug(BGFX_DEBUG_STATS);

	if (m_Width != old_with || m_Height != old_height)
	{
		bgfx::reset((uint32_t)m_Width, (uint32_t)m_Height, BGFX_RESET_VSYNC);
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xFF00FFFF, 1.0f, 0);
		bgfx::setViewRect(0, 0, 0, m_Width, m_Height);
		old_with = m_Width;
		old_height = m_Height;
	}

	bgfx::submit(0, program);
	bgfx::frame();

	// Don't look at this part :)
	counter++;

	if (counter > 1337)
	{
		counter = 0;
	}
	//

	glfwSwapBuffers(m_Window);
	glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
	glfwPollEvents();
}

bool Window::Setup(const char* title, int width, int height, bool use_imgui)
{
	if (!glfwInit())
	{
		return false;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!m_Window)
	{
		return false;
	}

	bgfx::renderFrame();

	bgfx::Init init;
	init.resolution.width = (uint32_t)m_Width;
	init.resolution.height = (uint32_t)m_Height;
	init.resolution.reset = BGFX_RESET_VSYNC;

#ifdef BX_PLATFORM_WINDOWS
	NOZ_LOG_INFO(NOZ_OBFUSCATE("Platform: Windows"));
	init.platformData.nwh = glfwGetWin32Window(m_Window);

#elif defined BX_PLATFORM_LINUX || BX_PLATFORM_BSD
	NOZ_LOG_INFO(NOZ_OBFUSCATE("Platform: Linux"));
	init.platformData.ndt = glfwGetX11Display();
	init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(m_Window);

#elif defined BX_PLATFORM_OSX
	NOZ_LOG_INFO(NOZ_OBFUSCATE("Platform: OSX"));
	init.platformData.nwh = glfwGetCocoaWindow(m_Window);
#endif

	if (!bgfx::init(init))
	{
		return false;
	}
	
	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xFF00FFFF, 1.0f, 0);
	bgfx::setViewRect(0, 0, 0, m_Width, m_Height);

	pcvDecl.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.end();

	vbh = bgfx::createVertexBuffer(bgfx::makeRef(cubeVertices, sizeof(cubeVertices)), pcvDecl);
	ibh = bgfx::createIndexBuffer(bgfx::makeRef(cubeTriList, sizeof(cubeTriList)));

	program = FileManager::LoadProgram(NOZ_OBFUSCATE("vs_cubes.bin"), NOZ_OBFUSCATE("fs_cubes.bin"));
	if (program.idx == USHRT_MAX)
	{
		NOZ_LOG_ERROR(NOZ_OBFUSCATE("Shaders not supported or not found"));
		return false;
	}

	return true;
}

void Window::Cleanup()
{
	bgfx::shutdown();
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

bool Window::Alive()
{
	return !glfwWindowShouldClose(this->m_Window) ? true : false;
}