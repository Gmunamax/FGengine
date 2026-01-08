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
// #include "params/position.hpp"
// #include "params/rotation.hpp"
#include "FGengine/shaders/shader.hpp"

template<typename PointType>
class WorldPoint{
	Uniforms::Umat4 mat;
	bool needupdate = true;
	PointType position{0};
	PointType rotation{0};

protected:
	void ProceedTransformations(){
		if(needupdate){
			mat = 1;
			if(rotation.x != 0)
				this->mat = glm::rotate(this->mat.GetValue(), glm::radians(rotation.x), glm::dvec3{1,0,0});
			if(rotation.y != 0)
				this->mat = glm::rotate(this->mat.GetValue(), glm::radians(rotation.y), glm::dvec3{0,1,0});
			if(rotation.z != 0)
				this->mat = glm::rotate(this->mat.GetValue(), glm::radians(rotation.z), glm::dvec3{0,0,1});
			this->mat = glm::translate(this->mat.GetValue(), position);
			needupdate = false;
		}
	}
	Uniforms::Umat4* GetMatrix(){
		return &mat;
	}
	void SendMatrix(){
		mat.Send();
	}
	void SetShader(Shader*& newshader){
		mat.SetShader(newshader->ToGL());
	}
	
	// ?
	// WorldPoint(const char* matrixname){
	// 	mat = new {matrixname};
	// };
	// ~WorldPoint(){
	// 	delete mat;
	// }


public:

	const PointType& GetPosition(){
		return position;
	}
	void SetPosition(PointType newposition){
		position = newposition;
		needupdate = true;
	}

	const PointType& GetRotation(){
		return rotation;
	}
	void SetRotation(PointType newrotation){
		rotation = newrotation;
		needupdate = true;
	}

	WorldPoint(const char* uniformname): mat(uniformname){}
};