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
#include "FGengine/structures/geometry.hpp"
#include "FGengine/structures/point.hpp"
#include "FGengine/structures/color.hpp"
#include "FGengine/properties/worldpoint.hpp"
#include "FGengine/special/shader.hpp"

namespace FGengine{

template<unsigned DimensionsCount, typename DataType>
class Camera: public PointTransform<DimensionsCount, DataType>{

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
			glm::mat<DimensionsCount+1, DimensionsCount, DataType> matrix;
			switch(projectionmode){
			case ProjectionMode::Frustum:
				glDepthFunc(GL_LESS);
				matrix = glm::perspective(fov, aspectratio, nearz, farz);
				break;

			case ProjectionMode::Ortho:
				glDepthFunc(GL_LESS);
				matrix = glm::ortho<DataType>(-aspectratio, aspectratio, -1.0f, 1.0f, nearz, farz);
				break;

			case ProjectionMode::Ui:
				glDepthFunc(GL_GEQUAL);
				matrix = glm::ortho<DataType>(-aspectratio, aspectratio, -1.0f, 1.0f);
				break;
			}
			Shader::SendUniformToAll<1>("fg_projectionmatrix", &matrix);
			needupdateprojection = false;
		}
	}

//projectionMatrix


//aspectratio

private:
	DataType aspectratio = 1;

public:
	void SetAspectRatio(const double& newaspectratio){
		UpdateProjectionPropertyValue(aspectratio, newaspectratio);
	}
	const double& GetAspectRatio() const{
		return aspectratio;
	}

//aspectratio


//fov

private:
	DataType fov = 75 * M_PI/180;

public:
	void SetFOV(const double& newfov){
		UpdateProjectionPropertyValue(fov, glm::radians(newfov));
	}
	const double& GetFOV() const{
		return fov;
	}

//fov


//viewdistance

private:
	DataType nearz = 1;
	DataType farz = 200;

public:
	void SetNearDistance(const DataType& newNearZ){
		UpdateProjectionPropertyValue(nearz, newNearZ);
	}
	void SetFarDistance(const DataType& newFarZ){
		UpdateProjectionPropertyValue(farz, newFarZ);
	}
	void SetDistance(const DataType& newNearZ, const DataType& newFarZ){
		SetNearDistance(newNearZ);
		SetFarDistance(newFarZ);
	}
	const double& GetNearDistance() const{
		return nearz;
	}
	const double& GetFarDistance() const{
		return farz;
	}

//viewdistance


// Move this somewhere (class Viewport) where this camera will be attached (viewport, background):

//viewport

private:
	Geometry2i viewportgeom;

public:
	void SetViewportGeom(const Geometry2i& newgeom){
		viewportgeom = newgeom;
		glViewport(newgeom.x,newgeom.y,newgeom.w,newgeom.h);

	}

	const Geometry2i& GetViewportGeom() const{
		return viewportgeom;
	}

	void Resize(const Geometry2i& newviewport){
		SetAspectRatio((double)newviewport.w/(double)newviewport.h);
		SetViewportGeom(newviewport);
		needupdateprojection = true;
	}

//viewport


//background

private:
	Color4d backgroundcolor {0,0,0,1};

public:
	void SetBackgroundColor(const Color4d& newbgcolor){
		backgroundcolor = newbgcolor;
	}
	const Color4d& GetBackgroundColor() const{
		return backgroundcolor;
	}

//background


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
