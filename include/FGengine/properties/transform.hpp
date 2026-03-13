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
#include "FGengine/structures/uniform.hpp"
#include "FGengine/special/shader.hpp"
#include "FGengine/structures/vector.hpp"
#include "FGengine/properties/worldpoint.hpp"

namespace FGengine{

template<unsigned DimensionsCount, typename DataType>
class Transform: public PointTransform<DimensionsCount, DataType>{

	Transform::PointType scale{1};

protected:
	Transform::MatrixType TransformScale(const Transform::MatrixType& matrix){
		return glm::scale(matrix, scale.toGlm());
	}

	Transform() {}

public:
	const Transform::PointType& GetScale(){
		return scale;
	}
	void SetScale(const Transform::PointType& newScale){
		scale = newScale;
		Transform::needupdate = true;
	}
};

}
