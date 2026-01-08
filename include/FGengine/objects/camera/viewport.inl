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