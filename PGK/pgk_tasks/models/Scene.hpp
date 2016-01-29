#ifndef SCENE_HPP
#define SCENE_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "types.hpp"
#include "Model.hpp"

class Scene {
public:
	std::vector< std::pair<Matrix_t,Model*> > Actors;
	virtual void LoadModelFromFile(std::string file_path);
	virtual ~Scene();

protected:
	std::vector<Mesh*> meshes;
	std::vector<Material*> materials;
	std::vector<Model*> models;
};

#endif