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
// #include "params/scale.hpp"
#include "FGengine/shaders/uniform.hpp"
#include "FGengine/shaders/shader.hpp"

template<typename PointType>
class Transform{

	Uniforms::Umat4 objm;

	bool needupdate = true;

	Uniforms::Umat3 normalm;
protected:
	void ProceedTransformations(){
		if(needupdate){

			objm = 1;
			objm = glm::translate(objm.GetValue(), position);

			if(rotation.x != 0)
				objm = glm::rotate(objm.GetValue(), glm::radians(rotation.x), glm::dvec3{1,0,0});
			if(rotation.y != 0)
				objm = glm::rotate(objm.GetValue(), glm::radians(rotation.y), glm::dvec3{0,1,0});
			if(rotation.z != 0)
				objm = glm::rotate(objm.GetValue(), glm::radians(rotation.z), glm::dvec3{0,0,1});

			objm = glm::scale(objm.GetValue(), scale);

			normalm = glm::transpose(glm::inverse(objm.GetValue()));
			
			needupdate = false;
		}
	}

	Uniforms::Umat4* GetMatrix(){
		return &objm;
	}

	void SendMatrix(){
		objm.Send();
		normalm.Send();
	}

	void SetShader(Shader*& newshader){
		objm.SetShader(newshader->ToGL());
		normalm.SetShader(newshader->ToGL());
	}

	Transform(){};

	PointType position{0};
	PointType rotation{0};
	PointType scale{1};


public:
	PointType& GetPosition(){
		return position;
	}
	void SetPosition(PointType newposition){
		position = newposition;
		needupdate = true;
	}

	

	PointType& GetRotation(){
		return rotation;
	}
	void SetRotation(PointType newrotation){
		rotation = newrotation;
		needupdate = true;
	}

	

	PointType& GetScale(){
		return scale;
	}
	void SetScale(PointType newscale){
		scale = newscale;
		needupdate = true;
	}

	Transform(const char* uniformname, const char* normaluniformname): objm(uniformname), normalm(normaluniformname){}

};