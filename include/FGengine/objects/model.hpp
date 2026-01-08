#pragma once
#include "FGengine/properties/transform/transform.hpp"
#include "FGengine/objects/model/datastorer.hpp"

template<typename VertexType>
class Model: public Transform<typename VertexType::VertexPosition::DataType>, public VertexDataStorage<VertexType>{
public:

	Model(): Model::Transform("fg_objectmatrix", "fg_normalmatrix"){};

	Shader* shader = &nullshader;

	void SetShader(Shader* newshader){
		shader = newshader;
		Model::Transform::SetShader(newshader);
	}

	void Init(){
		Model::VertexDataStorage::Init();
	}

	void Select(){
		Model::VertexDataStorage::Select();
		glUseProgram(shader->ToGL());
	}

	void Draw(){
		Model::Select();
		Model::ProceedTransformations();
		Model::SendMatrix();
		Model::DrawData();
	}
};
