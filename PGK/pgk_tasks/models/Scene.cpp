#include "Scene.hpp"

void Scene::LoadModelFromFile(std::string file_path) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(file_path, 
        aiProcess_Triangulate
        | aiProcess_GenSmoothNormals
        | aiProcess_GenUVCoords
        | aiProcess_PreTransformVertices
        | aiProcess_JoinIdenticalVertices
        | aiProcess_FindInstances
        | aiProcess_RemoveRedundantMaterials
        | aiProcess_FindInvalidData
        | aiProcess_OptimizeMeshes
        | aiProcess_ImproveCacheLocality
        | aiProcess_SortByPType
    );
  
  	if(!scene) {
  		throw "Import failed";
  	}

    //get relative directory path
    auto last_slash = file_path.find_last_of('/');
    std::string directory_path = "";
    if(last_slash != std::string::npos)
        directory_path = file_path.substr(0,last_slash+1);

  	// model
  	auto model = new Model;
  	models.push_back(model);
  	Actors.emplace_back(Matrix_t(1.0),model);

  	// materials
  	auto matStartIndex = materials.size();
  	for(unsigned int i=0 ; i < scene->mNumMaterials ; i++) {
        auto material = scene->mMaterials[i];
        aiString path;
        if(material->GetTexture(aiTextureType_DIFFUSE,0,&path) == AI_SUCCESS)
  		    materials.push_back(new Material(directory_path + path.C_Str()));
        else
            materials.push_back(new Material());
  	}

  	// meshes
  	for(unsigned int i=0 ; i < scene->mNumMeshes ; i++) {
  		auto their = scene->mMeshes[i];
  		auto my = new Mesh;
  		meshes.push_back(my);
  		
  		assert(their->HasFaces());
  		assert(their->HasPositions());
  		assert(their->HasTextureCoords(0));
  		assert(their->HasNormals());
  		assert(their->mPrimitiveTypes == aiPrimitiveType_TRIANGLE);

  		//material
  		auto material = materials[matStartIndex + their->mMaterialIndex];
  		model->Meshes.emplace_back(Matrix_t(1.0),my,material);

  		//faces
  		for(unsigned int i=0 ; i < their->mNumFaces ; i++) {
  			auto face = their->mFaces[i];
  			assert(face.mNumIndices == 3);
  			my->Faces.emplace_back(face.mIndices[0],face.mIndices[1],face.mIndices[2]);
  		}

  		//vertices
  		for(unsigned int i=0 ; i < their->mNumVertices ; i++) {
  			auto pos = their->mVertices[i];
  			auto uv = their->mTextureCoords[0][i];
  			auto norm = their->mNormals[i].Normalize();

  			my->Vertices.emplace_back(
  				Position_t(pos[0],pos[1],pos[2]),
  				TexPosition_t(uv[0],uv[1]),
  				Vector_t(norm[0],norm[1],norm[2])
  			);
  		}
  	}
}

Scene::~Scene() {
	for(auto ptr : models)
		delete ptr;

	for(auto ptr : meshes)
		delete ptr;

	for(auto ptr : materials)
		delete ptr;
}