// FGengine - a free and open-source library for game development
// Copyright (C) 2025, 2026 Gmunamax <https://github.com/Gmunamax/FGengine>

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, see <https://www.gnu.org/licenses/>.
#pragma once
#include "FGengine/properties/transform.hpp"
#include "FGengine/properties/mesh.hpp"
#include "FGengine/special/defaults.hpp"

namespace FGengine{

template<typename VertexType, typename ElementType>
class Model: public Transform<VertexType::VertexPosition::PropertyType::length(), typename VertexType::VertexPosition::PropertyType::valueType>, private Mesh<VertexType, ElementType>{
	bool visible = true;
	Shader* shader = Defaults::shader;

	Uniform<1, Model::Transform::MatrixType> objectMatrix{"fg_objectmatrix"};
	Uniform<1, Model::Transform::MatrixType> normalMatrix{"fg_normalmatrix"};

	void Transform(){
		objectMatrix = 1;
		objectMatrix = Model::Transform::TransformPosition(objectMatrix);
		objectMatrix = Model::Transform::TransformRotation(objectMatrix);
		objectMatrix = Model::Transform::TransformScale(objectMatrix);
		normalMatrix = glm::transpose(glm::inverse(objectMatrix.GetValue()));

		objectMatrix.Send();
		normalMatrix.Send();
	}

public:

	Model() {};


	void SetShader(Shader* newshader){
		shader = newshader;
		normalMatrix.SetShader(newshader);
		objectMatrix.SetShader(newshader);
		Model::Transform::SetShader(newshader);
	}

	void Init(){
		Model::Mesh::Init();
	}

	void Select(){
		Model::Mesh::Select();
		glUseProgram(shader->ToGL());
	}

	void Draw(){
		Model::Mesh::Select();
		Model::Transform();
		if(visible)
			Model::Mesh::Draw();
	}

	void Delete(){
		Model::Mesh::Delete();
	}

	void Load(const Model::Mesh::VertexesList& vertexes, const Model::Mesh::ElementsList& elements){
		Model::Mesh::Select();
		Model::Mesh::Load(vertexes, elements);
	}

	void SetVisible(const bool& newvisiblity){
		this->visible = newvisiblity;
	}
	const bool& GetVisiblity(){
		return visible;
	}
};

}
