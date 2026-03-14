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
#include <glm/gtc/matrix_transform.hpp>
#include "FGengine/special/shader.hpp"
#include "FGengine/structures/uniform.hpp"

namespace FGengine{

template<unsigned DimensionsCount, typename DataType>
class PointTransform{
protected:
	using MatrixType = glm::mat<DimensionsCount+1, DimensionsCount+1, DataType>;
	using PointType = Vector<DimensionsCount, DataType, VectorType::Point>;

private:
	bool needupdate = true;

	PointType position{0};
	PointType rotation{0};

protected:
	const bool& IsNeedUpdate(){
		return needupdate;
	}
	MatrixType TransformPosition(const MatrixType& matrix){
		return glm::translate(matrix, position.toGlm());
	}
	MatrixType TransformRotation(const MatrixType& matrix){
		MatrixType resultMatrix;
		if(rotation.x != 0)
			resultMatrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec<DimensionsCount, DataType>{1,0,0});
		if(rotation.y != 0)
			resultMatrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec<DimensionsCount, DataType>{0,1,0});
		if(rotation.z != 0)
			resultMatrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec<DimensionsCount, DataType>{0,0,1});
		return resultMatrix;
	}

	PointTransform() {}

public:
	const PointType& GetPosition(){
		return position;
	}
	void SetPosition(const PointType& newposition){
		position = newposition;
		needupdate = true;
	}

	const PointType& GetRotation(){
		return rotation;
	}
	void SetRotation(const PointType& newrotation){
		rotation = newrotation;
		needupdate = true;
	}
};

}
