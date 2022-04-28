#include "pch.hpp"
#include "Renderer.hpp"

using namespace Noz;

// Need to rework to draw an entire scene instead of passing in the entitylist
void Renderer::Render(std::vector<Entity*> entity_list)
{
	for (Entity* x : entity_list)
	{
		if (x->Has<ModelComponent, TransformComponent>())
		{
			for (Mesh mesh : x->Get<ModelComponent>()->Meshes)
			{
				bgfx::setTransform(&x->Get<TransformComponent>()->GetTransform());
				bgfx::setVertexBuffer(0, mesh.VBH);
				bgfx::setIndexBuffer(mesh.IBH);

				for (auto uniform : mesh.Mat.Uniforms)
				{
					bgfx::setUniform(uniform.first, uniform.second);
				}

				for (auto texture : mesh.Mat.Textures)
				{
					bgfx::setTexture(0, texture.first, texture.second);
				}

				bgfx::setState(mesh.Mat.State);
				bgfx::submit(0, mesh.Mat.Shader);
			}
		}
	}
}