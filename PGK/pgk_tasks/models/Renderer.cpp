#include "Renderer.hpp"
#include <tuple>

extern GLuint programID;

void Renderer::Render(Scene& scene,Camera& camera) const {
	camera.Bind();

	for(auto a : scene.Actors) {
		Matrix_t model_transform;
		Model* model;
		std::tie(model_transform,model) = a;

		for(auto tuple : model->Meshes) {
			Matrix_t mesh_transform;
			Mesh* mesh;
			Material* material;
			std::tie(mesh_transform,mesh,material) = tuple;

			material->Bind();
			mesh->Bind();
				
			// Draw the triangles !
			glDrawElements(
				GL_TRIANGLES,   // mode
				mesh->Faces.size()*3, // count
				INDEX_TYPE,		// type
				(void*)0        // element array buffer offset
			);

			mesh->Unbind();
		}

	}
}