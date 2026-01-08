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
void Camera<PointType>::SetViewportGeom(Geometry2i newgeom){
	glViewport(newgeom.x,newgeom.y,newgeom.w,newgeom.h);
	viewportgeom = newgeom;
}

template<typename PointType>
Geometry2i Camera<PointType>::GetViewportGeom(){
	return viewportgeom;
}

template<typename PointType>
void Camera<PointType>::Resize(Geometry2i newviewport){
	SetAspectRatio((double)newviewport.w/(double)newviewport.h);
	SetViewportGeom(newviewport);
	switch (cameratype) {
	case CAMERA_FRUSTUM:
		SetFrustum();
		break;
	case CAMERA_ORTHO:
		SetOrtho();
		break;
	case CAMERA_UI:
		SetUI();
		break;
	}
}