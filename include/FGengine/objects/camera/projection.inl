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
#ifdef __INTELLISENSE__
#include "FGengine/objects/camera.hpp"
#endif

template<typename PointType>
void Camera<PointType>::SetFrustum(){
	glDepthFunc(GL_LESS);
	
	cameratype = CAMERA_FRUSTUM;
}

template<typename PointType>
void Camera<PointType>::SetOrtho(){
	glDepthFunc(GL_LESS);
	
	cameratype = CAMERA_ORTHO;
}

template<typename PointType>
void Camera<PointType>::SetUI(){
	glDepthFunc(GL_GEQUAL);
	proj = glm::ortho<double>(-aspectratio,aspectratio,-1,1,nearz,farz);
	cameratype = CAMERA_UI;
}

template<typename PointType>
void Camera<PointType>::ProceedProjection(){
	switch(cameratype){
	case CAMERA_FRUSTUM:
		proj = glm::perspective(fov,aspectratio,nearz,farz);
		break;

	case CAMERA_ORTHO:
		proj = glm::ortho<double>(-aspectratio,aspectratio,-1,1,nearz,farz);
		break;

	case CAMERA_UI:
		proj = glm::ortho<double>(-aspectratio,aspectratio,-1,1,nearz,farz);
		break;
	}
	needupdateprojection = false;
}