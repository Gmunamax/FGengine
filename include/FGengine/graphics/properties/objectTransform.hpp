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
#include <glm/gtc/matrix_transform.hpp>

namespace FGengine::Graphics{

class ObjectTransform{
public:
	ObjectTransform(glm::vec3 position = {0,0,0}, glm::vec3 rotation = {0,0,0}):
		position{position},
		rotation{rotation}
	{}

	glm::mat4 Calculate(){
		glm::mat4 matrix;
		matrix = glm::translate(glm::mat4{1}, position);
		matrix = glm::rotate(matrix, rotation.x, {1,0,0});
		matrix = glm::rotate(matrix, rotation.y, {0,1,0});
		matrix = glm::rotate(matrix, rotation.z, {0,0,1});
		return matrix;
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
	glm::vec3 position;
	glm::vec3 rotation;
};

}
