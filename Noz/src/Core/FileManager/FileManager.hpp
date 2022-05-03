#pragma once

#include <bx/bx.h>
#include <bx/readerwriter.h>
#include <bgfx/bgfx.h>

namespace Noz
{
	class FileManager
	{
	public:
		//
		static void* Load(const char* file_path, uint32_t* size = NULL);

		///
		static void Unload(void* ptr);

		//
		static bgfx::ShaderHandle LoadShader(const char* name);
	};
}