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
#include "FGengine/graphics/structures/matrix.hpp"
#include "FGengine/graphics/structures/vector.hpp"

namespace FGengine::Graphics{

template<unsigned DimensionsCount, typename DataType>
class PointTransform{
public:
	using MatrixType = Matrix<DimensionsCount+1, DimensionsCount+1, DataType>;
	using VectorType = glm::vec3;
	using PositionType = VectorType;
	using RotationType = VectorType;

	PositionType GetPosition() const noexcept{
		return -position;
	}
	void SetPosition(const PositionType& newPosition) noexcept{
		position = -newPosition;
		needupdate = true;
	}

	RotationType GetRotation() const noexcept{
		return {-rotation.x, rotation.y, rotation.z};
	}
	void SetRotation(const RotationType& newRotation) noexcept{
		rotation = {-newRotation.x, newRotation.y, newRotation.z};
		needupdate = true;
	}

protected:
	const bool& IsNeedUpdate() noexcept{
		return needupdate;
	}
	MatrixType TransformPosition(const MatrixType& matrix){
		return glm::translate(matrix, position);
	}
	MatrixType TransformRotation(const MatrixType& matrix){
		MatrixType resultMatrix = matrix;
		if(rotation.x != 0)
			resultMatrix = glm::rotate(resultMatrix, glm::radians(rotation.x), glm::vec<DimensionsCount, DataType>{1,0,0});
		if(rotation.y != 0)
			resultMatrix = glm::rotate(resultMatrix, glm::radians(rotation.y), glm::vec<DimensionsCount, DataType>{0,1,0});
		if(rotation.z != 0)
			resultMatrix = glm::rotate(resultMatrix, glm::radians(rotation.z), glm::vec<DimensionsCount, DataType>{0,0,1});
		return resultMatrix;
	}

private:
	bool needupdate = true;

	PositionType position{0};
	PositionType rotation{0};
};

}
