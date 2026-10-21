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
#include "shader.hpp"
#include "properties/mesh.hpp"
#include "properties/objectMatrix.hpp"
#include <memory>
#include <span>

namespace FGengine::Graphics{

class Model{
public:
	Model(std::span<float> vertexes, const std::shared_ptr<Shader>& shader):
		shader{shader},
		mesh{vertexes}
	{}

	void Draw(){
		shader->Use();
		matrix.Update();
		mesh.Draw();
	}

	void SetPosition(const glm::vec3& newPosition){
		matrix.SetPosition(newPosition);
	}

	const glm::vec3& GetPosition() const{
		return matrix.GetPosition();
	}

	void SetRotation(const glm::vec3& newRotation){
		matrix.SetRotation(newRotation);
	}

	const glm::vec3& GetRotation() const{
		return matrix.GetRotation();
	}

private:
	std::shared_ptr<Shader> shader;
	Mesh mesh;
	ObjectMatrix matrix{shader->GetHandle()};
};

}
