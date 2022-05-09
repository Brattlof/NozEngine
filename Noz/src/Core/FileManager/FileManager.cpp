#include "pch.hpp"
#include "FileManager.hpp"

using namespace Noz;

bx::AllocatorI* FileManager::s_Allocator;
bx::FileReaderI* FileManager::s_FileReader;

class FileReader : public bx::FileReader
{
public:
	virtual bool open(const bx::FilePath& file_path, bx::Error* err) override
	{
		return bx::FileReader::open(file_path, err);
	}
};

void FileManager::Init()
{
	BX_PRAGMA_DIAGNOSTIC_PUSH();
	BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4459);
	BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC(NOZ_OBFUSCATE("-Wshadow"));
	bx::DefaultAllocator allocator;
	s_Allocator = &allocator;
	BX_PRAGMA_DIAGNOSTIC_POP();

	s_FileReader = BX_NEW(s_Allocator, FileReader);
}

void FileManager::Cleanup()
{
	delete s_FileReader;
}

const bgfx::Memory* FileManager::LoadMem(const char* file_path)
{
	if (bx::open(s_FileReader, file_path))
	{
		uint32_t size = (uint32_t)bx::getSize(s_FileReader);
		const bgfx::Memory* mem = bgfx::alloc(size + 1);
		bx::read(s_FileReader, mem->data, size, bx::ErrorAssert{});
		bx::close(s_FileReader);
		mem->data[mem->size - 1] = '\0';
		return mem;
	}

	NOZ_LOG_ERROR(NOZ_OBFUSCATE("Failed to load %s"), file_path);

	return NULL;
}

bgfx::ShaderHandle FileManager::LoadShader(const char* shader_name)
{
	std::string shader_path = NOZ_OBFUSCATE("assets/");

	switch (bgfx::getRendererType())
	{
		case bgfx::RendererType::Noop:	
		case bgfx::RendererType::Direct3D9:
		{
			shader_path += NOZ_OBFUSCATE("shaders/dx9/");
			break;
		}

		case bgfx::RendererType::Direct3D11:
		case bgfx::RendererType::Direct3D12:
		{
			shader_path += NOZ_OBFUSCATE("shaders/dx11/");
			break;
		}

		case bgfx::RendererType::Agc:
		case bgfx::RendererType::Gnm:
		{
			shader_path += NOZ_OBFUSCATE("shaders/pssl/");
			break;
		}

		case bgfx::RendererType::Metal:
		{
			shader_path += NOZ_OBFUSCATE("shaders/metal/");
			break;
		}
		case bgfx::RendererType::Nvn:
		{
			shader_path += NOZ_OBFUSCATE("shaders/nvn/");
			break;
		}

		case bgfx::RendererType::OpenGL:
		{
			shader_path += NOZ_OBFUSCATE("shaders/glsl/");
			break;
		}

		case bgfx::RendererType::OpenGLES:
		{
			shader_path += NOZ_OBFUSCATE("shaders/essl/");
			break;
		}

		case bgfx::RendererType::Vulkan:
		{
			shader_path += NOZ_OBFUSCATE("shaders/spirv/");
			break;
		}

		case bgfx::RendererType::WebGPU:
		{
			shader_path += NOZ_OBFUSCATE("shaders/spirv/");
			break;
		}

		case bgfx::RendererType::Count:
		default:
		{
			shader_path = NOZ_OBFUSCATE("???");
			NOZ_LOG_ERROR(NOZ_OBFUSCATE("?Shader?"));
			break;
		}
	}

	shader_path += shader_name;

	const bgfx::Memory* mem = LoadMem(shader_path.c_str());
	if (!mem)
	{
		return bgfx::ShaderHandle();
	}

	bgfx::ShaderHandle handle = bgfx::createShader(mem);
	bgfx::setName(handle, shader_name);
	
	return handle;
}

bgfx::ProgramHandle FileManager::LoadProgram(const char* vs_name, const char* fs_name)
{
	bgfx::ShaderHandle vsh = LoadShader(vs_name);
	if (vsh.idx == USHRT_MAX)
	{
		return bgfx::ProgramHandle();
	}

	bgfx::ShaderHandle fsh = LoadShader(fs_name);
	if (fsh.idx == USHRT_MAX)
	{
		return bgfx::ProgramHandle();
	}

	return bgfx::createProgram(vsh, fsh, true);
}