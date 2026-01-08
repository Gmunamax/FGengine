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
