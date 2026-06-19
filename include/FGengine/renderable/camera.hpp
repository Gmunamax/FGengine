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
#include "FGengine/properties/worldpoint.hpp"
#include "FGengine/special/shader.hpp"
#include "FGengine/structures/aspectratio.hpp"
#include "FGengine/special/defaults.hpp"

namespace FGengine{

template<unsigned DimensionsCount>
class Camera: public PointTransform<DimensionsCount, floatType>{
//viewMatrix

private:

	void ProceedTransformations(){
		if(Camera::PointTransform::IsNeedUpdate()){
			typename Camera::PointTransform::MatrixType matrix {1};
			matrix = Camera::PointTransform::TransformRotation(matrix);
			matrix = Camera::PointTransform::TransformPosition(matrix);
			Shader::SendUniformToAll<1>("fg_viewmatrix", &matrix);
		}
	}

//viewMatrix


//projectionMatrix

public:
	bool needupdateprojection = true;

private:
	template<typename T>
	void UpdateProjectionPropertyValue(T& target, const T& newvalue){
		target = newvalue;
		needupdateprojection = true;
	}

	void ProceedProjection(){
		if(needupdateprojection){
			glm::mat<DimensionsCount+1, DimensionsCount+1, floatType> matrix;
			switch(projectionmode){
			case ProjectionMode::Frustum:
				glDepthFunc(GL_LESS);
				matrix = glm::perspective<floatType>(fov, *aspectratio, nearz, farz);
				break;

			case ProjectionMode::Ortho:
				glDepthFunc(GL_LESS);
				matrix = glm::ortho<floatType>(-*aspectratio, *aspectratio, -1.0f, 1.0f, nearz, farz);
				break;

			case ProjectionMode::Ui:
				glDepthFunc(GL_GEQUAL);
				matrix = glm::ortho<floatType>(-*aspectratio, *aspectratio, -1.0f, 1.0f);
				break;
			}
			Shader::SendUniformToAll<1>("fg_projectionmatrix", &matrix);
			needupdateprojection = false;
		}
	}

//projectionMatrix


//aspectratio

private:
	AspectRatio* aspectratio = Defaults::aspectRatio;

public:
	void SetAspectRatio(AspectRatio* newaspectratio){
		UpdateProjectionPropertyValue(aspectratio, newaspectratio);
	}
	AspectRatio* GetAspectRatio() const{
		return aspectratio;
	}

//aspectratio


//fov

private:
	floatType fov = 75 * M_PI/180;

public:
	void SetFOV(const floatType& newfov){
		UpdateProjectionPropertyValue(fov, glm::radians(newfov));
	}
	const floatType& GetFOV() const{
		return fov;
	}

//fov


//viewdistance

private:
	floatType nearz = 1;
	floatType farz = 200;

public:
	void SetNearDistance(const floatType& newNearZ){
		UpdateProjectionPropertyValue(nearz, newNearZ);
	}
	void SetFarDistance(const floatType& newFarZ){
		UpdateProjectionPropertyValue(farz, newFarZ);
	}
	void SetDistance(const floatType& newNearZ, const floatType& newFarZ){
		SetNearDistance(newNearZ);
		SetFarDistance(newFarZ);
	}
	const floatType& GetNearDistance() const{
		return nearz;
	}
	const floatType& GetFarDistance() const{
		return farz;
	}

//viewdistance


//projection

public:
	enum class ProjectionMode{
		Frustum,	/* Perspective */
		Ortho,		/* Orthogonal */
		Ui			/* Orthogonal with inverted depth-test */
	};

private:
	ProjectionMode projectionmode = ProjectionMode::Ortho;

public:
	void SetProjectionMode(ProjectionMode newProjectionMode){
		projectionmode = newProjectionMode;
	}

//projection


//main

public:
	Camera() {};

	void ProceedUpdate(){
		glClearColor(backgroundcolor.r,backgroundcolor.g,backgroundcolor.b,backgroundcolor.a);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		Camera::ProceedTransformations();
		Camera::ProceedProjection();
	}

//main
};

}
