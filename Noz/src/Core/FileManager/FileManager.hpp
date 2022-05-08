#pragma once

#include <bx/bx.h>
#include <bx/debug.h>
#include <bx/file.h>
#include <bx/allocator.h>
#include <bgfx/bgfx.h>

namespace Noz
{
	class FileManager
	{
	private:
		static bx::AllocatorI* s_Allocator;
		static bx::FileReaderI* s_FileReader;

	public:
		static void Init();
		static void Cleanup();
		//
		static const bgfx::Memory* LoadMem(const char* file_path);

		//
		static bgfx::ShaderHandle LoadShader(const char* file_path);

		//
		static bgfx::ProgramHandle LoadProgram(const char* vs_file_path, const char* fs_file_path);
	};
}