#pragma once

#include <bgfx/bgfx.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Noz
{
	struct Material
	{
		bgfx::ProgramHandle Shader;
		uint64_t State;
		std::vector<std::pair<bgfx::UniformHandle, void*>> Uniforms;
		std::vector<std::pair<bgfx::UniformHandle, bgfx::TextureHandle>> Textures;
	};

	struct Mesh
	{
		bgfx::VertexBufferHandle VBH;
		bgfx::IndexBufferHandle IBH;
		Material Mat;
	};

	class ModelComponent : public BaseComponent
	{
	public:
		std::vector<Mesh> Meshes;

		void Reset();
		void Reset(std::vector<Mesh> meshes);

		void AddMesh(Mesh mesh) { Meshes.push_back(mesh); }
	};

	class TransformComponent : public BaseComponent
	{
	public:
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		void Reset();

		void Reset(const glm::vec3 translation, const glm::vec3 rotation, const glm::vec3 scale) 
		{
			Translation = translation;
			Rotation = rotation;
			Scale = scale;
		}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation) * rotation * glm::scale(glm::mat4(1.0f), Scale);
		}
	};
}