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
#include <glm/vec3.hpp>
#include <FGengine/graphics/structures/uniform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

namespace FGengine::Graphics{

class ObjectMatrix{
public:
	ObjectMatrix(unsigned int shaderProgram, glm::vec3 position = {0,0,0}, glm::vec3 rotation = {0, 0, 0}):
		position{position},
		rotation{rotation},
		objectMatrix{"model", FGengine::ShaderID{shaderProgram}}
	{
		Calculate();
	}

	void Update(){
		Calculate();
		objectMatrix.Send();
	}

	void SetPosition(const glm::vec3& newPosition){
		position = newPosition;
	}
	const glm::vec3& GetPosition() const{
		return position;
	}

	void SetRotation(const glm::vec3& newRotation){
		rotation = newRotation;
	}
	const glm::vec3& GetRotation() const{
		return rotation;
	}

private:
	void Calculate(){
		objectMatrix = glm::translate(glm::mat4{1}, position);
		objectMatrix = glm::rotate(objectMatrix.GetValue(), rotation.x, {1,0,0});
		objectMatrix = glm::rotate(objectMatrix.GetValue(), rotation.y, {0,1,0});
		objectMatrix = glm::rotate(objectMatrix.GetValue(), rotation.z, {0,0,1});
	}

	FGengine::Uniform<1, glm::mat4> objectMatrix;
	glm::vec3 position;
	glm::vec3 rotation;
};

}
